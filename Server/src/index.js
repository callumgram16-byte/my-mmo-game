// MMO Game Server
// Main entry point for the backend server

const express = require('express');
const http = require('http');
const socketIO = require('socket.io');
const dotenv = require('dotenv');

dotenv.config();

const app = express();
const server = http.createServer(app);
const io = socketIO(server, {
  cors: {
    origin: process.env.CLIENT_URL || 'http://localhost:3000',
    methods: ['GET', 'POST']
  }
});

const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Routes
app.get('/api/health', (req, res) => {
  res.json({ status: 'Server is running' });
});

// Socket.IO events
const playerConnections = new Map();

io.on('connection', (socket) => {
  console.log(`New player connected: ${socket.id}`);

  // Store player connection
  playerConnections.set(socket.id, {
    id: socket.id,
    position: { x: 0, y: 0, z: 0 },
    connectedAt: new Date()
  });

  // Player movement
  socket.on('player-move', (data) => {
    const player = playerConnections.get(socket.id);
    if (player) {
      player.position = data.position;
      // Broadcast to other players
      socket.broadcast.emit('player-moved', {
        playerId: socket.id,
        position: data.position
      });
    }
  });

  // Player disconnection
  socket.on('disconnect', () => {
    console.log(`Player disconnected: ${socket.id}`);
    playerConnections.delete(socket.id);
    io.emit('player-disconnected', { playerId: socket.id });
  });

  // Chat
  socket.on('chat-message', (data) => {
    io.emit('chat-message', {
      playerId: socket.id,
      message: data.message,
      timestamp: new Date()
    });
  });
});

// Start server
server.listen(PORT, () => {
  console.log(`MMO Server running on port ${PORT}`);
  console.log(`Environment: ${process.env.NODE_ENV || 'development'}`);
});

module.exports = app;