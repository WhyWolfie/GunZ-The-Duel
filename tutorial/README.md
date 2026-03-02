# GunZ: The Duel – Private Server Quick Setup Guide


## Quick Navigation

| # | Step                          | Main Resource                                                                                   | Est. Difficulty |
|---|-------------------------------|-------------------------------------------------------------------------------------------------|-----------------|
| 1 | Build jur13n 1.5 source       | [jur13n client 1.5](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/jur13n%20client%201.5) | ★★★★☆          |
| 2 | Set up database               | [SQL Server 2005](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/sql/2005)     | ★★☆☆☆          |
| 3 | Configure ODBC                | [ODBC setup](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/odbc)              | ★★☆☆☆          |
| 4 | Maps & editors                | [GTKRadiant](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/gtkradiant) · [GMD](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/debug/GMD) | ★★★☆☆    |
| 5 | Networking / Ports            | See table below                                                                                 | ★★☆☆☆          |
| 6 | Client files & tools          | [XML generators + .mrs tools](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/xmlgenerator) · [mrs folder](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/mrs) | ★★★☆☆          |
| 7 | Master movement mechanics     | [Movements guide](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/movements)    | ★★★★☆          |

---

## 1. Source Compilation

**Goal:** Upgrade & build jur13n GunZ 1.5 source (originally VS2003) on modern Visual Studio

📁 [tutorial/jur13n client 1.5](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/jur13n%20client%201.5)

**Recommended path (2026):**
- Visual Studio 2019 or 2022
- v142 / v143 toolset
- Windows 7/10/11 target platform
- Fix DirectX 9 SDK references
- Handle MBCS → Unicode migration if needed

---

## 2. Database Setup

**Most compatible choice:** SQL Server 2005 (or Express)

📁 [tutorial/sql/2005](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/sql/2005)

---

## 3. ODBC Connection

MatchServer & Locator → database bridge

📁 [tutorial/odbc](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/odbc)

---

## 4. Maps

| Tool          | Purpose                        | Folder Link                                                                 |
|---------------|--------------------------------|-----------------------------------------------------------------------------|
| GTKRadiant    | Map creation & editing         | [gtkradiant](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/gtkradiant)                |
| GMD           | Map debugging / conversion     | [debug/GMD](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/debug/GMD)                  |

---

## 5. Required Ports (TCP + UDP)

Open these ports in your firewall and router:

| Port   | Service / Component              | Purpose                                      | Protocol |
|--------|----------------------------------|----------------------------------------------|----------|
| 80     | Web server / launcher            | Rankings, news, downloads, patch server      | TCP      |
| 6000   | MatchServer                      | Primary game server port                     | TCP/UDP  |
| 7777   | Game server instance             | Stage / room hosting                         | TCP/UDP  |
| 7778   | Game server instance             | Additional stage / room                      | TCP/UDP  |
| 7779   | Game server instance             | Additional stage / room                      | TCP/UDP  |
| 9000   | MatchServer                      | Status, heartbeat, extra communication       | TCP/UDP  |
| 5100   | Agent server                     | Load balancing / additional game nodes       | TCP/UDP  |
| 8900   | Locator                          | Server list / master server discovery        | TCP/UDP  |

---

## 6. Client Preparation Tools

| Task                        | Tool / Generator              | Folder Link                                                                 |
|-----------------------------|-------------------------------|-----------------------------------------------------------------------------|
| Zitem.xml → Shop.xml        | Shop XML generator            | [xmlgenerator/shop](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/xmlgenerator/shop) |
| Generate maplist.xml        | Map XML generator             | [xmlgenerator/map](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/xmlgenerator/map)   |
| Pack / unpack .mrs files    | MRS Decompiler & tools        | [mrs](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/mrs)                              |
| Modern .mrs GUI             | Pro MRS GUI                   | [mrs/pro_mrs_gui](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/mrs/pro_mrs_gui)      |
| .mrs encrypt / decrypt      | GunnyCrypt                    | [mrs/gunnycrypt](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/mrs/gunnycrypt)        |

---

## 7. Movement System Deep Dive

Understand dashes, cancels, butterfly, flash step, wall running, K-style vs E-style

📁 [tutorial/movements](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/tutorial/movements)

Highly recommended — greatly improves testing and player experience.
