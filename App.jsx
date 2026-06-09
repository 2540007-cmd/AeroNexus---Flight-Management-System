import { BrowserRouter, Routes, Route, Navigate } from "react-router-dom";
import Login from "./pages/Login";
import Dashboard from "./pages/Dashboard";
import AddRecord from "./pages/AddRecord";
import CompanyRecords from "./pages/CompanyRecords";

function App() {
  const user = JSON.parse(localStorage.getItem("user"));

  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={user ? <Navigate to="/dashboard" /> : <Navigate to="/login" />} />
        <Route path="/login" element={<Login />} />
        <Route path="/dashboard" element={user ? <Dashboard /> : <Navigate to="/login" />} />
        <Route path="/add-record" element={user ? <AddRecord /> : <Navigate to="/login" />} />
        <Route path="/companies/:id/records" element={user ? <CompanyRecords /> : <Navigate to="/login" />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;