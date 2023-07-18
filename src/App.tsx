import { MapContainer, TileLayer, Marker, Popup } from 'react-leaflet';
import './App.css';

const position = {lat: 51.505, lng: -0.09}

function App() {
        
return(
  <MapContainer className='map' center={position} zoom={13} scrollWheelZoom={false}>
    <TileLayer
      attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
    />
    <Marker position={position}>
      <Popup>
        A pretty CSS3 popup. <br /> Easily customizable.
      </Popup>
    </Marker>
  </MapContainer>
);
    
}

export default App;