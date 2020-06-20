#!/bin/sh
cd ./zappy-graphics
npm run build
pkill node
npm run bridge &
cd ./dist && http-server
