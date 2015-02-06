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

# 在嘗試用 CI build Docker image 之前，先確定會正常 build！

--

## Vagrant 是你的好朋友...

--

### ☛ 先在 Vagrant 實驗 Docker

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

# 提交至 Git

## 在你的 Host machine 上：

```bash
$ git status

# 如有必要，提交異動內容進去...
$ git commit

# 遠端資訊
$ git remote -v

# 送至遠端
$ git push
```

.footnote[.red[*] 請確定你懂得以上指令的用意。 ]

---

# 去 GitHub 看看專案情況...


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
  - Automated Build  ☚ 會與 GitHub 連動！

--
3. Select

--

Live demo!

---

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
