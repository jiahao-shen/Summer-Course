# Week2-Day1

* 安装并运行storm

```bash
brew install zookeeper
brew install storm
```

* 修改/usr/local/Cellar/storm/1.2.2/libexec/conf/storm.yaml如下

![alt](https://github.com/jiahao-shen/SummerProject/tree/master/Week2/Day1/storm_yaml.png)

* 新建终端分别运行

```bash
storm nimbus
storm supervisor
storm ui
```

![alt](https://github.com/jiahao-shen/SummerProject/tree/master/Week2/Day1/iterm.png)

* 进入浏览器输入localhost:8080若看到如下页面则配置成功

![alt](https://github.com/jiahao-shen/SummerProject/tree/master/Week2/Day1/storm_ui.png)