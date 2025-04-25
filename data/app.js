let ledStatus = false;
let buzzerStatus = false;

// Theme toggle functionality
// Theme toggle functionality
const themeToggle = document.getElementById('theme-toggle');

// Check for saved theme preference or use default
if (localStorage.getItem('theme') === 'light') {
  document.documentElement.classList.remove('dark');
} else {
  // Set default to dark mode if no preference is found
  document.documentElement.classList.add('dark');
  localStorage.setItem('theme', 'dark');
}

// Toggle theme on button click
themeToggle.addEventListener('click', function() {
  if (document.documentElement.classList.contains('dark')) {
    // Switch to light mode
    document.documentElement.classList.remove('dark');
    localStorage.setItem('theme', 'light');
  } else {
    // Switch to dark mode
    document.documentElement.classList.add('dark');
    localStorage.setItem('theme', 'dark');
  }
});

function updateSensorData() {
  fetch('/sensor-data')
    .then(response => response.json())
    .then(data => {
      const value = data.waterLevel;
      
      // Update water level display
      document.getElementById("water-bar").style.width = `${value}%`;
      document.getElementById("water-level-text").textContent = `${Math.round(value)}%`;

      // Update color coding - FIXED VERSION
      const textElement = document.getElementById("water-level-text");
      
      // First remove all color classes
      textElement.classList.remove('red', 'orange', 'green');
      
      // Then add the appropriate class based on value
      if (value <= 25) {
        textElement.classList.add('red');
      } else if (value <= 75) {
        textElement.classList.add('orange');
      } else {
        textElement.classList.add('green');
      }
    })
    .catch(error => console.error('Sensor error:', error));
}

// Button handlers with proper state management
document.getElementById('start-cleaning').addEventListener('click', function() {
  const button = this;
  const action = ledStatus ? '/control/led-off' : '/control/led-on';
  
  button.classList.add('processing'); // Add processing state
  
  fetch(action)
    .then(response => {
      if (!response.ok) throw new Error('Network error');
      ledStatus = !ledStatus;
      button.textContent = ledStatus ? 'Stop Cleaning' : 'Start Cleaning';
    })
    .catch(error => console.error('LED error:', error))
    .finally(() => {
      button.classList.remove('processing'); // Ensure processing state is removed
    });
});

// Modify maintenance button handler
document.getElementById('maintenance').addEventListener('click', function() {
  const action = buzzerStatus ? '/control/buzzer-off' : '/control/buzzer-on';
  const button = this;
  
  button.classList.add('processing'); // Add processing state
  
  fetch(action)
    .then(response => {
      if (!response.ok) throw new Error('Network error');
      buzzerStatus = !buzzerStatus;
      button.textContent = buzzerStatus ? 'Stop Buzzer' : 'Maintenance';
    })
    .catch(error => console.error('Buzzer error:', error))
    .finally(() => {
      button.classList.remove('processing'); // Ensure processing state is removed
    });
});

document.getElementById('refill-water').addEventListener('click', function() {
  const button = this;
  button.disabled = true;
  button.classList.add('processing'); // Add processing state
  
  fetch('/control/refill-water')
    .then(response => {
      if (!response.ok) throw new Error('Network error');
      return response.text();
    })
    .then(data => console.log('Refill:', data))
    .catch(error => console.error('Pump error:', error))
    .finally(() => {
      button.disabled = false;
      button.classList.remove('processing'); // Ensure processing state is removed
    });
});

// Update sensor data every 100ms
setInterval(updateSensorData, 100);