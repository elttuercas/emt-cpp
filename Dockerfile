FROM docker.io/eltuercas/drogon

# Create application directory
WORKDIR /emt

# Copy licence
COPY ./LICENSE /emt/LICENSE

# Copy npm package files
COPY ./package.json /emt/package.json
COPY ./package-lock.json /emt/package-lock.json
COPY ./node_modules /emt/node_modules

# Copy release configuration file
COPY ./releaseconfig.json /emt/config.json

# Source SCSS files
COPY ./scss /emt/scss

# Source TS files and configuration
COPY ./ts /emt/ts
COPY ./tsconfig.json /emt/tsconfig.json

# Tailwind CSS config file
COPY ./tailwind.config.js /emt/tailwind.config.js

# Mix asset file
COPY ./webpack.mix.js /emt/webpack.mix.js

# Copy CMakeLists
COPY ./CMakeLists.txt /emt/CMakeLists.txt

# Copy C++ source files
COPY ./main.cc /emt/main.cc
COPY ./controllers /emt/controllers
COPY ./plugins /emt/plugins
COPY ./filters /emt/filters

# Copy CSP files
COPY ./views /emt/views

# Copy database model spec file and C++ model source files
COPY ./models /emt/models

# Install create webpack production files
RUN npm run prod

# Change to build directory and compile the application
WORKDIR /emt/build
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make

# Run web application
CMD ["/emt/build/emt-cpp"]
