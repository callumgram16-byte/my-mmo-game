# MMO Architecture Documentation

## Overview

The My MMO Game is structured as a client-server architecture with Unreal Engine 5 as the client and a Node.js backend server handling game logic, persistence, and multiplayer coordination.

## System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                Unreal Engine 5 Client                    │
│  ┌─────────────────┐  ┌─────────────┐  ┌──────────────┐ │
│  │ Gameplay Logic  │  │  Character  │  │ Inventory UI │ │
│  └─────────────────┘  └─────────────┘  └──────────────┘ │
└──────────────────────┬──────────────────────────────────┘
                       │ Socket.IO / HTTP
┌──────────────────────▼──────────────────────────────────┐
│                Node.js Backend Server                    │
│  ┌─────────────────┐  ┌──────────────┐  ┌────────────┐ │
│  │ Authentication  │  │ Player Mgmt  │  │World State │ │
│  └─────────────────┘  └──────────────┘  └────────────┘ │
└──────────────────────┬──────────────────────────────────┘
                       │ Database / Cache
        ┌──────────────┼──────────────┐
        ▼              ▼              ▼
    PostgreSQL     Redis Cache    File Storage
```

## Core Systems

### 1. Character System
- **CharacterBase**: Base class for all player and NPC characters
- **Stats**: Health, Mana, Experience, Level
- **Progression**: Experience-based leveling system

### 2. Inventory System
- **InventoryComponent**: Manages items, equipment, and carry weight
- **InventoryItem**: Data structure for items with stats and properties
- **Item Types**: Weapons, Armor, Consumables, Quest items, Crafting materials
- **Rarity System**: Common, Uncommon, Rare, Epic, Legendary

### 3. Networking
- **Socket.IO**: Real-time player movement and interaction synchronization
- **Player Connection Management**: Tracks active players and their state
- **Position Updates**: Broadcasts player positions to nearby players

### 4. Authentication
- **JWT-based**: Secure token authentication
- **Password Hashing**: bcryptjs for secure password storage
- **Session Management**: Redis-backed session storage

## Technologies

### Client-Side (Unreal Engine 5)
- **Engine**: Unreal Engine 5
- **Language**: C++ / Blueprints
- **Networking**: Socket.IO client
- **Input System**: Enhanced Input System (UE5)

### Server-Side (Node.js)
- **Framework**: Express.js
- **Real-time**: Socket.IO
- **Database**: PostgreSQL or MongoDB
- **Cache**: Redis
- **Authentication**: JWT

---

**Last Updated**: 2026-06-25
**Status**: Active Development