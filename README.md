# 💰 Profit Calculator — Inflation-Aware Investment Simulator

> A terminal-based financial simulation tool that helps you project long-term investments while adjusting for inflation.  
> Built in C, with CSV and chart output powered by Gnuplot.

---

### 📜 Project Overview

**Profit Calculator** is a simple yet powerful CLI program written in C that simulates compound investment growth over a specified period.  
It accounts for both interest (growth) and inflation (devaluation) and outputs a clean `.csv` dataset along with a visual chart.  
It’s ideal for analyzing financial plans!

---

### ⚙️ Features

- 🧾 **Custom currency input** ($ / ₺ / € / etc.)
- 📈 **Compound interest support** (monthly rate)
- 📉 **Yearly inflation adjustment**
- 📅 **Time range in months**
- 📄 **Outputs a `.csv` file** with:
  - Raw value over time
  - Inflation-adjusted value
  - Formatted amounts for readability
- 📊 **Gnuplot integration**:
  - PNG chart with two plotted lines:
    - Raw growth
    - Inflation-adjusted growth
- 📂 **Filename customization** for saving results
- 🧮 **Localized formatting** for large numbers

---

## 🛠️ Technologies Used

- Language: **C**
- Dependencies: `math.h`, `stdio.h`, `stdlib.h`, `string.h`
- External Tool: [**Gnuplot**](http://www.gnuplot.info/) (for chart generation)
- Output format: **CSV**, **PNG**

---

### 📦 Build & Run Instructions

#### 🧰 Requirements
- GCC compiler
- Gnuplot installed and in your PATH

#### 🔨 Build

```bash
./wCurrency
```

#### 🤫 Upcoming Features

- API intergration for realtime currency comparison.
- Running website w/UI for easy of use.
- Edge Case handling. Since this is *just a work progress*.

#### ⭐️ Feel free to drop a star!
