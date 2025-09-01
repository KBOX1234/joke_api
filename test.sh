 
#!/bin/bash

BASE_URL="http://localhost:3214"

echo "=== Testing /joke ==="
curl -s "${BASE_URL}/joke"
echo -e "\n"

# User credentials
EMAIL="test@example.com"
PASSWORD="password123"

echo "=== Testing /sign_in ==="
SIGNUP_RESPONSE=$(curl -s -X POST "${BASE_URL}/sign_in" \
  -H "Content-Type: application/json" \
  -d "{\"email\":\"${EMAIL}\",\"password\":\"${PASSWORD}\"}")
echo "${SIGNUP_RESPONSE}"
echo -e "\n"

# Extract key from JSON response
KEY=$(echo "${SIGNUP_RESPONSE}" | grep -oP '(?<="key":")[^"]+')
echo "User key: ${KEY}"

echo "=== Testing /login ==="
LOGIN_RESPONSE=$(curl -s -X POST "${BASE_URL}/login" \
  -H "Content-Type: application/json" \
  -d "{\"email\":\"${EMAIL}\",\"password\":\"${PASSWORD}\"}")
echo "${LOGIN_RESPONSE}"
echo -e "\n"

# Extract key from login
KEY=$(echo "${LOGIN_RESPONSE}" | grep -oP '(?<="key":")[^"]+')
echo "Login key: ${KEY}"

echo "=== Testing /submit ==="
curl -s -X POST "${BASE_URL}/submit" \
  -H "Content-Type: application/json" \
  -d "{\"key\":\"${KEY}\",\"word\":\"jump\",\"type\":\"verb\"}"
echo -e "\n"
