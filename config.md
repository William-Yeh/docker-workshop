行前準備 Part 2：預載範例程式碼
===

為了節省課程現場下載程式及相關資源的時間及頻寬，請學員先在**網路暢通的地方**，根據指示備妥必要的軟體及設定。

如果網路順暢，整個過程可能會花上數十分鐘，請耐心等候。

&nbsp;

☛ 程式範例會在每一梯次開課前一週才定案，因此，建議**等開課前一週再進行下列步驟**。

☛ 進行以下步驟之前，請先確定 VirtualBox 之【預設機器資料夾】所在的磁碟上，仍有足夠空間，以容納各虛擬機內容及預載之 Docker 映像檔。建議至少要預留 15 GB：
![預留 VirtualBox 虛擬機所需空間](img/vbox-diskspace.png)


&nbsp;


### 步驟一：Fork 本次 workshop 範例程式

1. 登入 GitHub 網站： https://github.com/

2. 開啟 https://github.com/William-Yeh/docker-workshop

3. 按右上角的 ![Fork Button](img/icon-github-fork.png) 按鈕。

4. 幾秒鐘之內，你應該會被自動導引到自己帳號底下的 docker-workshop 專案。


### 步驟二：開啟終端機，以進行後續步驟

Linux 使用者：請使用 xterm 或任何你慣用的終端機軟體。

Mac 使用者：請使用終端機 (Terminal)、iTerm 或任何你慣用的終端機軟體。

Windows 使用者：

1. 請先以「不含任何中文字」的使用者帳號，登入 Windows（否則會在某些 Vagrant 相關步驟出錯）。
2. 以『系統管理者』權限，打開【命令提示字元】軟體（否則**可能**會在某些 Vagrant 相關步驟出錯）。




### 步驟三：下載 workshop 範例程式

請先切換到你選定的工作目錄，譬如：

   ```shell
   cd YOUR_OWN_WORKING_DIRECTORY
   ```

再下載範例：

   ```shell
   git clone https://github.com/你的帳號/docker-workshop.git
   ```



### 步驟四：切換至此 workshop 目錄

```shell
cd docker-workshop
```

#### ⇡ 以上所列的幾個步驟，如有不清楚的，請見示範錄影：

[![Docker Workshop - How to Fork Project](http://img.youtube.com/vi/n2ogtWHZRzo/0.jpg)](http://youtu.be/n2ogtWHZRzo)

---
<br/>

#### ⇣ 以下所列的幾個步驟，如有不清楚的，請見示範錄影：

[![Docker Workshop - How to Setup Lab Environment](http://img.youtube.com/vi/0aaMQ8u9Dvg/0.jpg)](http://youtu.be/0aaMQ8u9Dvg)



### 步驟五：安裝必要的 Vagrant 擴充套件

➤ 錄影 0:00～01:16 片段。

```shell
vagrant plugin install vagrant-hosts
vagrant plugin install vagrant-vbox-snapshot
```


### 步驟六：初始化 Vagrant 虛擬機

耗時最久的，就是這個步驟，請耐心等候。

➤ 錄影 01:23～57:25 片段。

- 如果你的電腦是 Mac 或 Linux，請輸入：

  ```shell
  ./setup-vagrant
  ```

- 如果你的電腦是 Windows，請輸入：

  ```shell
  setup-vagrant
  ```


### 步驟七：快照 (snapshot)

➤ 錄影 57:38～58:42 片段。

先替這一批 snapshot 取個易於辨識追溯的名稱，建議以現在時間 *mm/dd-HH:MM* 為名。

假設現在時間是 `02/19-08:00` (Feb 19, 08:00)，請輸入以下指令：

```shell
vagrant snapshot take main      02/19-08:00
vagrant snapshot take alice     02/19-08:00
vagrant snapshot take bob       02/19-08:00
vagrant snapshot take centos    02/19-08:00
vagrant snapshot take registry  02/19-08:00
```


### 步驟八：確認 snapshot 已完成

➤ 錄影 59:08～片尾。

```shell
vagrant snapshot list main
vagrant snapshot list alice
vagrant snapshot list bob
vagrant snapshot list centos
vagrant snapshot list registry
```
