import time
import statistics
import urllib.request
from concurrent.futures import ThreadPoolExecutor

URL = "http://localhost:8080/predict"
NUM_REQUESTS = 60
CONCURRENCY = 10

SAMPLE_TEXTS = [
    "WINNER! Free prize, call now to claim!",
    "hey are we still on for lunch tomorrow",
    "URGENT your account has been suspended click here",
    "can you send me the notes from class",
    "congratulations you have been selected for a reward",
    "let's meet at the library around 5"
]

def send_request(i):
    text = SAMPLE_TEXTS[i % len(SAMPLE_TEXTS)]
    data = text.encode("utf-8")
    req = urllib.request.Request(URL, data=data, method="POST")

    start = time.perf_counter()
    try:
        with urllib.request.urlopen(req, timeout=5) as res:
            res.read()
            ok = True
    except Exception as e:
        print(f"FAILED: {e}")
        ok = False
        
    elapsed = time.perf_counter() - start

    return ok, elapsed

def main():
    print(f"sending {NUM_REQUESTS} requests, concurrency {CONCURRENCY}")

    latencies = []
    failures = 0

    start_total = time.perf_counter()

    with ThreadPoolExecutor(max_workers=CONCURRENCY) as pool:
        results = pool.map(send_request, range(NUM_REQUESTS))

    for ok, elapsed in results:
        if ok:
            latencies.append(elapsed)
        else:
            failures += 1

    total_time = time.perf_counter() - start_total

    print()
    print(f"total time: {total_time:.3f}s")
    print(f"successful: {len(latencies)}  failed: {failures}")
    print(f"requests/sec: {len(latencies) / total_time:.2f}")

    if latencies:
        print(f"avg latency: {statistics.mean(latencies) * 1000:.2f}ms")
        print(f"min latency: {min(latencies) * 1000:.2f}ms")
        print(f"max latency: {max(latencies) * 1000:.2f}ms")

if __name__ == "__main__":
    main()
