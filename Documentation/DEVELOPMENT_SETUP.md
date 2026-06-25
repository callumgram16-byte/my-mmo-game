# Development Setup Guide

## Prerequisites

### For Client Development
- **Unreal Engine 5.0+** - Download from [Epic Games Launcher](https://www.epicgames.com/store/en-US/download)
- **Visual Studio 2022** - With C++ development tools
- **Git** - For version control

### For Server Development
- **Node.js 16+** - Download from [nodejs.org](https://nodejs.org/)
- **npm** or **yarn** - Comes with Node.js
- **PostgreSQL 12+** - Database server
- **Redis** - For caching and sessions

## Client Setup (Unreal Engine)

### Step 1: Clone Repository
```bash
git clone https://github.com/callumgram16-byte/my-mmo-game.git
cd my-mmo-game
```

### Step 2: Generate Visual Studio Project
1. Right-click on `my-mmo-game.uproject`
2. Select "Generate Visual Studio project files"
3. Open `my-mmo-game.sln` in Visual Studio

### Step 3: Compile Project
1. In Visual Studio, select Development Editor configuration
2. Build the solution (Ctrl + Shift + B)
3. Wait for compilation to complete

### Step 4: Open in Unreal Editor
```bash
start my-mmo-game.uproject
```

## Server Setup (Node.js)

### Step 1: Install Dependencies
```bash
cd Server
npm install
```

### Step 2: Configure Environment
```bash
cp .env.example .env
nano .env
```

### Step 3: Start Development Server
```bash
npm run dev
```

The server will start on `http://localhost:3000`

### Step 4: Test Connection
```bash
curl http://localhost:3000/api/health
```

Expected response:
```json
{ "status": "Server is running" }
```

## Troubleshooting

### Client Issues

**Unreal Engine won't open project**
- Delete `Binaries/`, `Intermediate/`, `Saved/` folders
- Right-click `.uproject` → Generate Visual Studio files
- Recompile

### Server Issues

**Port already in use**
```bash
lsof -i :3000
kill -9 <PID>
```

---

**Last Updated**: 2026-06-25
**Status**: Active