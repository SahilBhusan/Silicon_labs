const demoReports = [
  { species: "No bird activity", confidence: 95, lux: 362, rms: 512, alert: false },
  { species: "Unknown bird", confidence: 72, lux: 399, rms: 640, alert: false },
  { species: "Unknown bird", confidence: 78, lux: 436, rms: 704, alert: true }
];

const state = {
  index: 0,
  reports: []
};

function renderReport(report) {
  document.getElementById("species").textContent = report.species;
  document.getElementById("confidence").textContent = `${report.confidence}%`;
  document.getElementById("lux").textContent = `${report.lux} lx`;
  document.getElementById("audio-rms").textContent = report.rms;

  state.reports.unshift(report);
  state.reports = state.reports.slice(0, 8);

  const reportList = document.getElementById("reports");
  reportList.innerHTML = "";
  for (const item of state.reports) {
    const row = document.createElement("li");
    row.textContent = `${new Date().toLocaleTimeString()} - ${item.species}, ${item.confidence}% confidence, ${item.lux} lx${item.alert ? ", alert" : ""}`;
    reportList.appendChild(row);
  }
}

function nextDemoReport() {
  const base = demoReports[state.index % demoReports.length];
  state.index += 1;
  renderReport({
    ...base,
    lux: base.lux + state.index * 7,
    rms: base.rms + state.index * 11
  });
}

nextDemoReport();
setInterval(nextDemoReport, 3000);
