#!/bin/sh
# Compiles and runs every C program under ChapterNN.
# Collects every failure (does not stop at the first). Failures are printed as a
# workflow annotation, so they can be read without signing in to GitHub.
#
#   CC=gcc sh ci/build.sh
#   CC=clang SAN=1 sh ci/build.sh      # AddressSanitizer + UBSan (leaks included)
#
# Program layouts:
#   ChapterNN/name.c      single-file program
#   ChapterNN/name/       all .c files in the folder are compiled as one program
# A file (or the main file of a folder) whose first line says "RUN: compile only"
# is only compiled.
set -u
CC="${CC:-gcc}"
CFLAGS="-std=c11 -Wall -Wextra -pedantic -O1 -g"
[ "$CC" = "gcc" ] && CFLAGS="$CFLAGS -Werror"
[ "${SAN:-0}" = "1" ] && CFLAGS="$CFLAGS -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all"
LIBS="-lm"
summary="${GITHUB_STEP_SUMMARY:-/dev/stdout}"
label="${RUNNER_OS:-local}/$CC"
[ "${SAN:-0}" = "1" ] && label="$label+asan"
tmp=$(mktemp -d)
failed=""
ok=0

printf '\n## C programs — %s\n\n| Program | Result |\n|---|---|\n' "$label" >> "$summary"

for p in Chapter*/*.c Chapter*/*/; do
    [ -e "$p" ] || continue
    p=${p%/}
    if [ -d "$p" ]; then
        srcs=$(ls "$p"/*.c 2>/dev/null)
        [ -n "$srcs" ] || continue
        first=$(grep -l 'int main' $srcs | head -1)
        incl="-I$p"
    else
        srcs="$p"
        first="$p"
        incl=""
    fi
    name=$(echo "$p" | tr '/.' '__')
    exe="$tmp/$name"
    if ! $CC $CFLAGS $incl $srcs -o "$exe" $LIBS > "$tmp/$name.log" 2>&1; then
        failed="$failed $p"
        printf '| `%s` | **DID NOT COMPILE** |\n' "$p" >> "$summary"
        continue
    fi
    if [ -n "$first" ] && head -1 "$first" | grep -q 'RUN: compile only'; then
        ok=$((ok + 1))
        printf '| `%s` | compiled |\n' "$p" >> "$summary"
        continue
    fi
    run="$tmp/run_$name"
    mkdir -p "$run"
    if (cd "$run" && timeout 20 "$exe" < /dev/null > "$tmp/$name.out" 2>&1); then
        ok=$((ok + 1))
        printf '| `%s` | ok |\n' "$p" >> "$summary"
    else
        rc=$?
        { echo "exit code $rc"; tail -25 "$tmp/$name.out"; } >> "$tmp/$name.log"
        failed="$failed $p"
        printf '| `%s` | **FAILED (%s)** |\n' "$p" "$rc" >> "$summary"
    fi
    leftover=$(ls -A "$run")
    if [ -n "$leftover" ]; then
        failed="$failed $p"
        echo "files left behind: $leftover" >> "$tmp/$name.log"
        printf '| `%s` | **LEFT FILES** |\n' "$p" >> "$summary"
    fi
done

[ -z "$failed" ] && { printf '\n%s programs all passed on %s.\n' "$ok" "$label"; exit 0; }

printf '\n### Failures\n' >> "$summary"
for p in $failed; do
    name=$(echo "$p" | tr '/.' '__')
    printf '\n<details><summary>%s</summary>\n\n```\n' "$p" >> "$summary"
    head -40 "$tmp/$name.log" >> "$summary"
    printf '```\n\n</details>\n' >> "$summary"
done

# Collect the failures in one annotation (line breaks encoded as %0A).
msg=$(for p in $failed; do
        name=$(echo "$p" | tr '/.' '__')
        printf '%s:\n' "$p"
        grep -E 'error|warning|exit code|files left behind|undefined reference|ERROR: |runtime error|SUMMARY' "$tmp/$name.log" \
            | head -4 | sed 's/^/  /'
      done | sed 's/%/%25/g' | awk '{printf "%s%%0A", $0}')
printf '::error title=Chapter programs failed on %s::%s\n' "$label" "$msg"

printf '\nFailed:%s\n' "$failed"
exit 1
