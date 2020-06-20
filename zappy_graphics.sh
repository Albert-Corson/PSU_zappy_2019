#!/bin/sh
cd ./zappy-graphics
npm run build
npm run bridge &
cd ./dist
http-server &
cd ../../
