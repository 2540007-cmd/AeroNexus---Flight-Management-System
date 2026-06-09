import { useState } from "react";
import { useNavigate } from "react-router-dom";

function AddRecord() {
  const [airport, setAirport] = useState("");
  const [destination, setDestination] = useState("");
  const [modelno, setModelno] = useState("");
  const [distance, setDistance] = useState("");
  const [fuelConsumed, setFuelConsumed] = useState("");
  const [status, setStatus] = useState("Completed");
  const [message, setMessage] = useState("");
  const navigate = useNavigate();

  const handleSubmit = async () => {
    const body = `airport=${airport}&destination=${destination}&modelno=${modelno}&distance=${distance}&fuelConsumed=${fuelConsumed}&status=${status}`;

    const res = await fetch("http://localhost:8080/records", {
      method: "POST",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: body,
    });

    const data = await res.json();
    if (data.success) {
      setMessage("Record added successfully!");
      setTimeout(() => navigate("/dashboard"), 1500);
    } else {
      setMessage("Failed to add record.");
    }
  };

  return (
    <div className="min-h-screen bg-gray-900 text-white p-8">
      <div className="max-w-xl mx-auto">
        <button onClick={() => navigate("/dashboard")} className="text-gray-400 hover:text-white mb-6 block">← Back to Dashboard</button>
        <h1 className="text-3xl font-bold text-blue-400 mb-8">Add Flight Record</h1>

        {message && <p className="text-green-400 mb-4">{message}</p>}

        <div className="bg-gray-800 rounded-2xl p-8 flex flex-col gap-4">
          <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="From (Airport)" value={airport} onChange={e => setAirport(e.target.value)} />
          <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="To (Destination)" value={destination} onChange={e => setDestination(e.target.value)} />
          <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Plane Model No" value={modelno} onChange={e => setModelno(e.target.value)} />
          <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Distance (km)" value={distance} onChange={e => setDistance(e.target.value)} />
          <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Fuel Consumed (L)" value={fuelConsumed} onChange={e => setFuelConsumed(e.target.value)} />
          <select className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" value={status} onChange={e => setStatus(e.target.value)}>
            <option value="Completed">Completed</option>
            <option value="Scheduled">Scheduled</option>
            <option value="Cancelled">Cancelled</option>
          </select>
          <button onClick={handleSubmit} className="bg-blue-600 hover:bg-blue-700 text-white font-bold py-3 rounded-lg transition">
            Add Record
          </button>
        </div>
      </div>
    </div>
  );
}

export default AddRecord;