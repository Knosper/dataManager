# Use an official Node runtime as a parent image
FROM node:14

# Set the working directory in the container
WORKDIR /app

# Copy package.json and package-lock.json (if available) into the container at /app
COPY package*.json ./

# Install any needed packages specified in package*.json
RUN npm install

# If you are building your code for production
# RUN npm ci --only=production

# Bundle app's source code inside the Docker image
COPY . .

# Your app binds to port 3000, so you'll use the EXPOSE instruction to have it mapped by the docker daemon
EXPOSE 3000

# Define environment variable
ENV NODE_ENV=production

# Run npm start when the container launches
CMD ["npm", "start"]
