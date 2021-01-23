FROM drogonframework/drogon

# Install npm to perform TS compilation and CSS minimisation and concatenation
RUN apt update && apt install -y npm node-typescript
RUN npm install -g n && n stable

# Create application directory
RUN mkdir /emt
WORKDIR /emt

# Copy npm package files
COPY ./package.json /emt/package.json
COPY ./package-lock.json /emt/package-lock.json
COPY ./node_modules /emt/node_modules

# Copy release configuration file
COPY ./releaseconfig.json /emt/config.json

# Source CSS files
COPY ./css /emt/css

# Source TS files and configuration
COPY ./ts /emt/ts
COPY ./tsconfig.json /emt/tsconfig.json

# Tailwind CSS config file
COPY ./tailwind.config.js /emt/tailwind.config.js

# Mix asset file
COPY ./webpack.mix.js /emt/webpack.mix.js

# Install npm dependencies and create webpack production files
RUN npm run prod

# Copy CMakeLists
COPY ./CMakeLists.txt /emt/CMakeLists.txt

# Copy C++ source files
COPY ./main.cc /emt/main.cc
COPY ./controllers /emt/controllers
COPY ./plugins /emt/plugins
COPY ./filters /emt/filters

# Copy LSP files
COPY ./views /emt/views

# Copy database model spec file and C++ model source files
COPY ./models /emt/models

# Create application build directory
RUN mkdir /emt/build

# Change to build directory and compile the application
WORKDIR /emt/build
RUN cmake ..
RUN make

# Run web application
CMD ["emt-cpp"]
