# How Compiler
## Docker Compose
<details>
<summary>Running with Docker Compose</summary>

Docker Compose is the easiest way to run TibiaCore server with all necessary dependencies. Follow these steps:

```bash
# Clone the repository
git clone git@github.com:davagrad/TibiaCore.git
cd TibiaCore

# Build and start the server using Docker Compose
docker-compose up -d

# Check server status
docker-compose ps

# View server logs
docker-compose logs tfs

# Stop the server
docker-compose down
```

Docker Compose will:
1. Set up a MariaDB database container
2. Build the TibiaCore server from source
3. Configure the server to connect to the database
4. Start both services with proper networking

The server uses the following ports:
- 7171: Login port
- 7172: Game port
- 80: Web interface

You can customize database credentials and other settings by editing the `docker-compose.yml` file before starting the server.
</details>
<hr>
