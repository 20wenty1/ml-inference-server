FROM python:3.12-slim

WORKDIR /app

COPY requirements.txt .
RUN grep -v "^torch==" requirements.txt > requirements_no_torch.txt
RUN pip install --no-cache-dir --index-url https://download.pytorch.org/whl/cpu torch==2.13.0
RUN pip install --no-cache-dir -r requirements_no_torch.txt

COPY worker/ ./worker/
COPY models/ ./models/

CMD ["python", "-m", "worker.server"]

