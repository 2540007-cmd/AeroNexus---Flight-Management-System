import { useEffect, useState } from "react";
import { useParams, useLocation, useNavigate } from "react-router-dom";

function CompanyRecords() {
  const { id } = useParams();
  const location = useLocation();
  const navigate = useNavigate();
  const companyName = location.state?.companyName || "Company";
  const [records, setRecords] = useState([]);
  const [showAdd, setShowAdd] = useState(false);
  const [editIndex, setEditIndex] = useState(null);
  const [form, setForm] = useState({ airport: "", destination: "", modelno: "", distance: "", fuelConsumed: "", status: "Completed" });
  const [message, setMessage] = useState("");
  const user = JSON.parse(localStorage.getItem("user"));

  useEffect(() => {
    fetchRecords();
  }, []);

  const fetchRecords = () => {
    fetch(`http://localhost:8080/companies/${id}/records`)
      .then(res => res.json())
      .then(data => setRecords(data));
  };

  const resetForm = () => setForm({ airport: "", destination: "", modelno: "", distance: "", fuelConsumed: "", status: "Completed" });

  const handleAdd = async () => {
    const body = `airport=${encodeURIComponent(form.airport)}&destination=${encodeURIComponent(form.destination)}&modelno=${encodeURIComponent(form.modelno)}&distance=${form.distance}&fuelConsumed=${form.fuelConsumed}&status=${encodeURIComponent(form.status)}`;
    const res = await fetch(`http://localhost:8080/companies/${id}/records`, {
      method: "POST",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: body,
    });
    const data = await res.json();
    if (data.success) {
      setMessage("Record added!");
      setShowAdd(false);
      resetForm();
      fetchRecords();
      setTimeout(() => setMessage(""), 2000);
    }
  };

  const handleEdit = (index) => {
    setEditIndex(index);
    setForm({
      airport: records[index].airport,
      destination: records[index].destination,
      modelno: records[index].modelno,
      distance: records[index].distance,
      fuelConsumed: records[index].fuelConsumed,
      status: records[index].status,
    });
    setShowAdd(false);
  };

  const handleUpdate = async () => {
    const body = `airport=${encodeURIComponent(form.airport)}&destination=${encodeURIComponent(form.destination)}&modelno=${encodeURIComponent(form.modelno)}&distance=${form.distance}&fuelConsumed=${form.fuelConsumed}&status=${encodeURIComponent(form.status)}`;
    const res = await fetch(`http://localhost:8080/companies/${id}/records/${editIndex}`, {
      method: "PUT",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: body,
    });
    const data = await res.json();
    if (data.success) {
      setMessage("Record updated!");
      setEditIndex(null);
      resetForm();
      fetchRecords();
      setTimeout(() => setMessage(""), 2000);
    }
  };

  const handleDelete = async (index) => {
    if (!window.confirm("Delete this record?")) return;
    await fetch(`http://localhost:8080/companies/${id}/records/${index}`, { method: "DELETE" });
    fetchRecords();
  };

  const statusColor = (status) => {
    if (status === "Completed") return "bg-green-600";
    if (status === "Cancelled") return "bg-red-600";
    return "bg-yellow-500";
  };

  const FormPanel = ({ onSave, onCancel, saveLabel }) => (
    <div className="bg-gray-800 rounded-2xl p-6 mb-6 flex flex-col gap-3">
      <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="From (Airport)" value={form.airport} onChange={e => setForm({ ...form, airport: e.target.value })} />
      <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="To (Destination)" value={form.destination} onChange={e => setForm({ ...form, destination: e.target.value })} />
      <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Plane Model No" value={form.modelno} onChange={e => setForm({ ...form, modelno: e.target.value })} />
      <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Distance (km)" value={form.distance} onChange={e => setForm({ ...form, distance: e.target.value })} />
      <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Fuel Consumed (L)" value={form.fuelConsumed} onChange={e => setForm({ ...form, fuelConsumed: e.target.value })} />
      <select className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" value={form.status} onChange={e => setForm({ ...form, status: e.target.value })}>
        <option value="Completed">Completed</option>
        <option value="Scheduled">Scheduled</option>
        <option value="Cancelled">Cancelled</option>
      </select>
      <div className="flex gap-3">
        <button onClick={onSave} className="flex-1 bg-green-600 hover:bg-green-700 text-white font-bold py-3 rounded-lg">{saveLabel}</button>
        <button onClick={onCancel} className="flex-1 bg-gray-600 hover:bg-gray-700 text-white font-bold py-3 rounded-lg">Cancel</button>
      </div>
    </div>
  );

  return (
    <div className="min-h-screen bg-gray-900 text-white p-8">
      <div className="max-w-5xl mx-auto">
        <button onClick={() => navigate("/dashboard")} className="text-gray-400 hover:text-white mb-6 block">← Back to Dashboard</button>

        <div className="flex justify-between items-center mb-8">
          <div>
            <p className="text-gray-400 text-sm">Company</p>
            <h1 className="text-3xl font-bold text-blue-400">{companyName}</h1>
            <p className="text-gray-400 text-sm mt-1">Flight Records</p>
          </div>
          {user?.type === "admin" && (
            <button onClick={() => { setShowAdd(!showAdd); setEditIndex(null); resetForm(); }} className="bg-blue-600 hover:bg-blue-700 text-white px-4 py-2 rounded-lg">
              + Add Record
            </button>
          )}
        </div>

        {message && <p className="text-green-400 mb-4">{message}</p>}

        {showAdd && <FormPanel onSave={handleAdd} onCancel={() => { setShowAdd(false); resetForm(); }} saveLabel="Save Record" />}
        {editIndex !== null && <FormPanel onSave={handleUpdate} onCancel={() => { setEditIndex(null); resetForm(); }} saveLabel="Update Record" />}

        <div className="bg-gray-800 rounded-2xl overflow-hidden">
          <table className="w-full text-left">
            <thead className="bg-gray-700 text-gray-400 text-sm">
              <tr>
                <th className="p-4">From</th>
                <th className="p-4">To</th>
                <th className="p-4">Model</th>
                <th className="p-4">Distance</th>
                <th className="p-4">Fuel</th>
                <th className="p-4">Status</th>
                {user?.type === "admin" && <th className="p-4">Actions</th>}
              </tr>
            </thead>
            <tbody>
              {records.map((r, i) => (
                <tr key={i} className="border-t border-gray-700">
                  <td className="p-4">{r.airport}</td>
                  <td className="p-4">{r.destination}</td>
                  <td className="p-4">{r.modelno}</td>
                  <td className="p-4">{r.distance} km</td>
                  <td className="p-4">{r.fuelConsumed} L</td>
                  <td className="p-4">
                    <span className={`${statusColor(r.status)} text-white text-xs px-2 py-1 rounded-full`}>
                      {r.status}
                    </span>
                  </td>
                  {user?.type === "admin" && (
                    <td className="p-4 flex gap-2">
                      <button onClick={() => handleEdit(i)} className="bg-yellow-500 hover:bg-yellow-600 text-white text-sm px-3 py-1 rounded-lg">Edit</button>
                      <button onClick={() => handleDelete(i)} className="bg-red-600 hover:bg-red-700 text-white text-sm px-3 py-1 rounded-lg">Delete</button>
                    </td>
                  )}
                </tr>
              ))}
              {records.length === 0 && (
                <tr>
                  <td colSpan="7" className="p-8 text-center text-gray-500">No records found</td>
                </tr>
              )}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}

export default CompanyRecords;