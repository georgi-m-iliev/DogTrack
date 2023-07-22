import './App.css';
import { useState, useEffect } from 'react';
import Map from './Map';

const initialPosition = {lat: 42.427918, lng: 25.631706}

function App() {
    const [position, setPosition] = useState(initialPosition);
    
    const askPort = async () => {
        const port = await navigator.serial.requestPort();
        console.log(port);
    };

    navigator.serial.addEventListener("connect", (e) => {
        console.log("Port connected" + e.target);
    });

    navigator.serial.addEventListener("disconnect", (e) => {
        console.log("Port disconnected" +  e.target);
    });

    return(
        <div>
            <button onClick={askPort}>Ask Port</button>
            <Map/>
        </div>
    );

}

export default App;