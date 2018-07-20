# Week2

* 安装并运行storm

```bash
brew install zookeeper
brew install storm
```

* 修改/usr/local/Cellar/storm/1.2.2/libexec/conf/storm.yaml如下

![alt](https://github.com/jiahao-shen/SummerProject/blob/master/Week2/storm_yaml.png)

* 新建终端分别运行

```bash
storm nimbus
storm supervisor
storm ui
```

![alt](https://github.com/jiahao-shen/SummerProject/blob/master/Week2/iterm.png)

* 进入浏览器输入localhost:8080若看到如下页面则配置成功

![alt](https://github.com/jiahao-shen/SummerProject/blob/master/Week2/storm_ui.png)

* 安装maven

```bash
brew install maven
```

* 修改maven仓库地址改为阿里云(配置文件地址/usr/local/Cellar/maven/1.2.2/libexec/conf/setting.xml)

```xml
<mirrors>
  <mirror>
    <id>alimaven</id>
    <name>aliyun maven</name>
    <url>http://maven.aliyun.com/nexus/content/groups/public/</url>
    <mirrorOf>central</mirrorOf>
  </mirror>
</mirrors>
```

* 进入storm-starter路径(默认/usr/local/Cellar/storm/1.2.2/libexec/examples/storm-starter)

* 编译部署

```bash
cd storm-starter
mvn compile     #编译
mvn package     #打包
cd target
storm jar storm-starter-1.2.2.jar org.apache.storm.starter.WordCountTopology WordCount      #自行替换类名
```

* 刷新浏览器即可看到部署结果

![alt](https://github.com/jiahao-shen/SummerProject/blob/master/Week2/storm_starter2.png)

```bash
storm list
```

![alt](https://github.com/jiahao-shen/SummerProject/blob/master/Week2/storm_starter1.png)
