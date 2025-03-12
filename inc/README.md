# Project Setup for VSCode Dev Containers

This guide will walk you through the steps to set up your development environment using [VSCode Dev Containers](https://code.visualstudio.com/docs/devcontainers/overview), install the necessary libraries (including `libcamera`), and deploy the project to a Raspberry Pi.

## 1. Setting Up the Development Container with VSCode

### Prerequisites

- [Docker](https://www.docker.com/get-started) installed on your machine.
- [Visual Studio Code](https://code.visualstudio.com/) installed on your machine.
- The [Remote - Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) for VSCode installed.
- A clone of the repository containing the `.devcontainer` folder and your Dockerfile.

### Opening the Project in a Dev Container

1. **Clone the repository** containing the `.devcontainer` folder and Dockerfile:

   ```bash
   git clone <repository-url>
   cd <project-directory>
    ```
2. **Open the project in VSCode**:

    ```
    code .
    ```
3. When VSCode opens the project, it will automatically detect the `.devcontainer` folder and prompt you to reopen the project in the container. If not, you can manually select Reopen in Container from the VSCode Command Palette (`Cmd+Shift+P` or `Ctrl+Shift+P`).

This will build and start the development container based on the settings defined in the `Dockerfile` and `.devcontainer/devcontainer.json`.

## 2. Libraries

### 2.1 Setting up Wiring Pi

The dev container automatically sets up `WiringPi` in your local environment. H

    wget https://github.com/WiringPi/WiringPi/releases/download/3.10/wiringpi_3.10_armhf.deb
    sudo dpkg -i ./wiringpi_3.10_armhf.deb
    sudo apt-get install -f

### 2.2 Setting up `libcamera`

To work with `libcamera`, you'll need to build it from source within the container. Run these commands. This will set up the cross-compilation enviironment and define the toolchain. Make sure you update the library cache with `ldconfig.`

    git clone https://git.libcamera.org/libcamera/libcamera.git
    cd libcamera
    meson setup build --cross-file ../armhf_cross.txt
    ninja -C build install -j 4
    ldconfig
    

## 3. Deploying to Raspberry Pi

Once you have built the project, you can deploy it to a Raspberry Pi using the provided deploy script. The script copies the built files to the Raspberry Pi over SCP.

### 3.1 Using the Deploy Script

Copy the deploy script to your container or local machine if you haven't already.

Run the deploy script with the desired Raspberry Pi number. The script takes the Raspberry Pi number as an argument (default is `71` if no argument is passed):

```
./deploy.sh
```

For example, to deploy to raspberrypi13, use:

```
./deploy.sh 13
```

The script will copy the built `bobcar` binary from the `bin/` directory to the Raspberry Pi’s `Documents` folder.
