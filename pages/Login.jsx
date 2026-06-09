import { useState } from "react";
import { useNavigate } from "react-router-dom";

function Login() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [isSignup, setIsSignup] = useState(false);
  const [error, setError] = useState("");
  const navigate = useNavigate();

 const handleSubmit = async () => {
    if (!username || !password) {
      setError("Please enter username and password");
      return;
    }

    const endpoint = isSignup ? "/signup" : "/login";
    const body = `username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}`;

    try {
      const res = await fetch(`http://localhost:8080${endpoint}`, {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: body,
      });

      const text = await res.text();
      const data = JSON.parse(text);

      if (data.success) {
        localStorage.setItem("user", JSON.stringify({ username: data.username, type: data.type }));
        window.location.href = "/dashboard";
      } else {
        setError(data.message);
      }
    } catch (err) {
      setError("Connection error: " + err.message);
    }
  };

  return (
    <div className="min-h-screen bg-gray-900 flex items-center justify-center">
      <div className="bg-gray-800 p-10 rounded-2xl w-full max-w-md">
        <h1 className="text-3xl font-bold text-blue-400 text-center mb-2">✈ AeroNexus</h1>
        <p className="text-gray-400 text-center mb-8">{isSignup ? "Create an account" : "Sign in to continue"}</p>

        {error && <p className="text-red-400 text-sm text-center mb-4">{error}</p>}

        <div className="mb-4">
          <label className="text-gray-400 text-sm mb-1 block">Username</label>
          <input
            className="w-full bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500"
            placeholder="Enter username"
            value={username}
            onChange={e => setUsername(e.target.value)}
          />
        </div>

        <div className="mb-6">
          <label className="text-gray-400 text-sm mb-1 block">Password</label>
          <input
            type="password"
            className="w-full bg-gray-700 text-white rounded-lg px-4 py-3 outline-none focus:ring-2 focus:ring-blue-500"
            placeholder="Enter password"
            value={password}
          onChange={e => setPassword(e.target.value)}
          onKeyDown={e => e.key === "Enter" && handleSubmit()}
          />
        </div>

        <button
          onClick={handleSubmit}
          className="w-full bg-blue-600 hover:bg-blue-700 text-white font-bold py-3 rounded-lg transition"
        >
          {isSignup ? "Sign Up" : "Login"}
        </button>

        <p className="text-gray-400 text-center mt-6 text-sm">
          {isSignup ? "Already have an account?" : "Don't have an account?"}
          <span
            className="text-blue-400 cursor-pointer ml-1"
            onClick={() => { setIsSignup(!isSignup); setError(""); }}
          >
            {isSignup ? "Login" : "Sign Up"}
          </span>
        </p>
      </div>
    </div>
  );
}

export default Login;