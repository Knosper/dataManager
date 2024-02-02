# Use Node.js official image as the base image
FROM node:latest

# Create an app user
RUN groupadd -r app && useradd -r -g app -G audio,video app \
    && mkdir -p /home/app && chown -R app:app /home/app

# Set the working directory in the container to /app
WORKDIR /app

# Install dependencies for Electron
RUN apt-get update && apt-get install -y \
    libgtk-3-0 \
    libnss3 \
    libxss1 \
    libasound2 \
    libxtst6 \
    libgbm1 \
    xauth \
    xvfb \
	nano \
    && rm -rf /var/lib/apt/lists/*

# Copy package.json and package-lock.json (if available)
COPY package*.json ./

# Set the working directory ownership to the new app user
# Make sure this is done after copying the package files
RUN chown -R app:app /app

# Switch to the new app user
USER app

# Install Node.js dependencies
RUN npm install

# Copy the main application
COPY . .

# Make sure the ownership is set correctly for all copied files
USER root
RUN chown -R app:app /app
USER app

# Expose the port the app runs on
EXPOSE 8080

# Run the application
CMD ["tail", "-f", "/dev/null"]

#CMD ["npm", "start"]
