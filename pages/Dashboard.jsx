import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";

function Dashboard() {
  const [companies, setCompanies] = useState([]);
  const [showAddCompany, setShowAddCompany] = useState(false);
  const [newCompany, setNewCompany] = useState({ name: "", planes: "", terminals: "" });
  const [message, setMessage] = useState("");
  const navigate = useNavigate();
  const user = JSON.parse(localStorage.getItem("user"));

  useEffect(() => {
    fetchCompanies();
  }, []);

  const fetchCompanies = () => {
    fetch("http://localhost:8080/companies")
      .then(res => res.json())
      .then(data => setCompanies(data));
  };

  const handleAddCompany = async () => {
    const body = `name=${encodeURIComponent(newCompany.name)}&planes=${newCompany.planes}&terminals=${newCompany.terminals}`;
    const res = await fetch("http://localhost:8080/companies", {
      method: "POST",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: body,
    });
    const data = await res.json();
    if (data.success) {
      setMessage("Company added!");
      setShowAddCompany(false);
      setNewCompany({ name: "", planes: "", terminals: "" });
      fetchCompanies();
      setTimeout(() => setMessage(""), 2000);
    }
  };

  const handleDeleteCompany = async (id) => {
    if (!window.confirm("Delete this company?")) return;
    await fetch(`http://localhost:8080/companies/${id}`, { method: "DELETE" });
    fetchCompanies();
  };

  return (
    <div className="min-h-screen bg-gray-900 text-white p-8">

      <div className="flex justify-between items-center max-w-5xl mx-auto mb-8">
        <div className="flex items-center gap-3">
          <div className="bg-blue-600 rounded-full w-10 h-10 flex items-center justify-center font-bold text-lg">
            {user?.username?.charAt(0).toUpperCase()}
          </div>
          <div>
            <p className="font-bold text-white">{user?.username}</p>
            <p className="text-xs text-gray-400 capitalize">{user?.type}</p>
          </div>
        </div>
        <h1 className="text-3xl font-bold text-blue-400">✈ AeroNexus</h1>
        <button
          onClick={() => { localStorage.removeItem("user"); window.location.href = "/login"; }}
          className="bg-red-600 hover:bg-red-700 text-white px-4 py-2 rounded-lg"
        >
          Logout
        </button>
      </div>

      {message && <p className="text-green-400 text-center mb-4">{message}</p>}

      <div className="max-w-5xl mx-auto">
        <div className="flex justify-between items-center mb-4">
          <h2 className="text-2xl font-bold">Companies</h2>
          {user?.type === "admin" && (
            <button
              onClick={() => setShowAddCompany(!showAddCompany)}
              className="bg-blue-600 hover:bg-blue-700 text-white px-4 py-2 rounded-lg"
            >
              + Add Company
            </button>
          )}
        </div>

        {showAddCompany && (
          <div className="bg-gray-800 rounded-2xl p-6 mb-6 flex flex-col gap-3">
            <input className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Company Name" value={newCompany.name} onChange={e => setNewCompany({ ...newCompany, name: e.target.value })} />
            <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Number of Planes" value={newCompany.planes} onChange={e => setNewCompany({ ...newCompany, planes: e.target.value })} />
            <input type="number" className="bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500" placeholder="Number of Terminals" value={newCompany.terminals} onChange={e => setNewCompany({ ...newCompany, terminals: e.target.value })} />
            <button onClick={handleAddCompany} className="bg-green-600 hover:bg-green-700 text-white font-bold py-3 rounded-lg">Save Company</button>
          </div>
        )}

        <div className="bg-gray-800 rounded-2xl overflow-hidden">
          <table className="w-full text-left">
            <thead className="bg-gray-700 text-gray-400 text-sm">
              <tr>
                <th className="p-4">ID</th>
                <th className="p-4">Company Name</th>
                <th className="p-4">Planes</th>
                <th className="p-4">Terminals</th>
                <th className="p-4">Records</th>
                {user?.type === "admin" && <th className="p-4">Actions</th>}
              </tr>
            </thead>
            <tbody>
              {companies.map((c) => (
                <tr key={c.id} className="border-t border-gray-700 hover:bg-gray-750">
                  <td className="p-4 text-gray-400">{c.id}</td>
                  <td className="p-4 font-bold">{c.name}</td>
                  <td className="p-4">{c.planes}</td>
                  <td className="p-4">{c.terminals}</td>
                  <td className="p-4">
                    <button
                      onClick={() => navigate(`/companies/${c.id}/records`, { state: { companyName: c.name } })}
                      className="bg-blue-600 hover:bg-blue-700 text-white text-sm px-3 py-1 rounded-lg"
                    >
                      View Records
                    </button>
                  </td>
                  {user?.type === "admin" && (
                    <td className="p-4 flex gap-2">
                      <button
                        onClick={() => handleDeleteCompany(c.id)}
                        className="bg-red-600 hover:bg-red-700 text-white text-sm px-3 py-1 rounded-lg"
                      >
                        Delete
                      </button>
                    </td>
                  )}
                </tr>
              ))}
              {companies.length === 0 && (
                <tr>
                  <td colSpan="6" className="p-8 text-center text-gray-500">No companies found</td>
                </tr>
              )}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}

export default Dashboard;