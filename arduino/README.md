# Dog Track Arduino

## Introduction

This project consists of two nodes. One acts as a **Transmitter** of the received GPS coordinates (from the NEO-6M module) and one acts as a **Receiver** of said coordinates. The **Receiver** then relays the coordinates through a HC-05 Bluetooth module to the [DogTrack App](https://github.com/georgi-m-iliev/DogTrackFlutter), which displays the coordinates on a map.