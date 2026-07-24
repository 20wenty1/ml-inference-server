#!/bin/bash

HOST="http://localhost:8080"
pass=0
fail=0

check() {
    if echo "$2" | grep -q "$3"; then
        echo "PASS: $1"
        pass=$((pass+1))
    else
        echo "FAIL: $1"
        echo "  got: $2"
        fail=$((fail+1))
    fi
}

r=$(curl -s $HOST/)
check "health endpoint" "$r" "running"

r=$(curl -s -X POST $HOST/predict -d "WINNER! Free prize, call now to claim!")
check "spam detection" "$r" "spam"

r=$(curl -s -X POST $HOST/predict -d "hey are we still on for lunch tomorrow")
check "ham detection" "$r" "ham"

r=$(curl -s $HOST/nonsense)
check "404 on unknown path" "$r" "not found"

r=$(curl -s -X POST $HOST/predict -d "")
check "400 on empty body" "$r" "empty request body"

echo ""
echo "passed: $pass  failed: $fail"

if [ $fail -gt 0 ]; then
    exit 1
fi
