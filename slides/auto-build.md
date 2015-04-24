name: inverse
layout: true
class: center, middle, inverse

---

.percent100[.center[![bg](img/WiseMonkeys-3.jpg)]]

# CI 示範／<br/>叫 Docker Hub 幫你建 image

???

Img src: http://getacover.com/covers/9/8619_1532.jpg

---

layout: false

# Lab setup

.pull-left[
## VMs

1. `main`:
   - `up`
   - `ssh`

2. `registry`:
   - `up`
]

.pull-right[
## Lab directory
- `build-redis`
- `build-redis-el5` (quiz)
]


---

template: inverse

# Continuous Integration

---

# CI concepts

- Code

- Build / Package

- Artifact Registry

- Deployment

- Configuration


---

# CI and Docker

角色分工

- Code

- Build / Package

- Artifact Registry

- Deployment

- Configuration

---

class: center, middle

# 用 CI 去 build Docker image 前，<br/>先確定會正常 build Docker！

--

### ☛ 先在 本機端 實驗 Docker

--

### ☛ ... 再轉移經驗到 CI 上

---

# 先確定有正常 build

```bash
$ docker build .
```

.percent50[.right[![bg](img/app-building-dockerway.svg)]]

---

# 也正常 run 了...

---

class: code120

# 提交至 Git

## 在你的 Host machine 上：

```bash
% git status

# 如有必要，提交異動內容進去...
% git commit

# 遠端資訊
% git remote -v

# 送至遠端
% git push
```

.footnote[.red[*] 請確定你懂得以上指令的用意。 ]

---

# 去 GitHub 看看專案情況...


---

class: center, middle

# Authorization - 2 Parts

### 1. GitHub
### 2. Docker Hub

---

# GitHub／授權

Log in to GitHub: https://github.com/

1. Switch to your project (repository)

--
2. Settings

--
3. Webhooks & Services

--
4. Add service
   - Docker  ☚ 勾選這個

--
5. Add service  ☚ 確認


---

# Docker Hub／綁定帳號

Log in to Docker Hub: https://registry.hub.docker.com/

--
1. Settings

--
2. Linked Accounts

--
3. Link to your GitHub/Bitbucket Account

---

# Docker Hub／新建 Repository

1. View Profile

--
2. Add Repository
  - Repository
  - Automated Build  ☚ 勾選這個，與 GitHub 連動！

--
3. Select

--

Live demo!

---

class: code120

# Pull it from Docker Hub!

```bash
$ docker pull  `你的帳號`/`你的_IMAGE_名稱`
```

---

# Commit changes to GitHub...

- 考慮加上 tag 或 branch...


---

# Quiz

Do it for `build-redis-el5` directory.

---

class: center, middle

# Questions?
