
# Svelte Frontend Dockerfile
FROM node:24-slim

WORKDIR /app

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy source code
COPY . .

# Expose port
EXPOSE 5173

# Start development server (voor development)
CMD ["npm", "run", "dev", "--", "--host", "0.0.0.0"]