import pytest
from worker.inference import predict

def test_returns_valid_label():
    result = predict("hello there")
    assert result in ("spam", "ham")

def test_obvious_spam():
    text = "WINNER!! Free prize, call now to claim your reward"
    assert predict(text) == "spam"

def test_obvious_ham():
    text = "hey are we still on for lunch tomorrow"
    assert predict(text) == "ham"

def test_empty_string():
    result = predict("")
    assert result in ("spam", "ham")

def test_long_input():
    text = "free money " * 500
    result = predict(text)
    assert result in ("spam", "ham")