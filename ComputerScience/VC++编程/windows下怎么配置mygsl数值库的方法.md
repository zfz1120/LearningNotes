windows下配置mygsl数值计算c程序库的方法



转载自：[windows下怎么配置mygsl数值库的方法](http://blog.sina.com.cn/s/blog_a3d16f5e0101fk4c.html)

如果你是做科学研究的话，现在很少的计算能够用解析的方式给出解答，在很多的情况下要进行数值计算解决手中的问题。数值计算的软件现在很多，包括MATLAB，mathmatic等等，这些软件的优点也是很明确的，这些软件很好上手，很容易学会进行一些简单的编程计算，但是如果你要进行一些复杂的大型运算的话，只用这些软件的话会感到很吃力，因为这些软件的方便使用的优点也恰恰限制了他们的运算速度。今天我就要向大家介绍下一种c++数值运算库的使用，这个c++库叫做mygsl。

gsl（GNU scientific library）是提供给c和c++程序员的数值计算库，他是具有GNU公共许可证的免费软件，该库提供了十分广泛的数值运算的函数，包括随机数发生器，特殊函数和最小二次方拟合等等。

mygsl是基于gsl开发的开源数值计算项目，该项目致力于优化gsl的易用性和高效性。库包括linux平台和windows平台的发行版。鉴于很多人的电脑安装的是windows的操作系统，我们先介绍下怎么在windows平台下怎么使用mygsl数值库：

测试环境：win7系统下的vs2008

软件包：[http://david.geldreich.free.fr/dev.html](http://david.geldreich.free.fr/dev.html)下载最新版的gsl for windows版本，这个二进制文件中包含了可以在windows平台下使用的c++库文件，下载后解压到任意文件夹目录下，这样数值库就安装成功了（纯绿色安装）。

接下来就是对visual studio进行配置，打开vs2008，工具-选项-项目和解决方案-vc++目录平台win32-将包含文件和库文件添加到对应的include和library目录中；最后对自己的项目进行配置，打开project，项目属性，当前配置为debug，配置属性-连接器-输入，右边附加依赖项添加cblas.lib和gsl.lib，配置属性-c++代码生成-运行时库改成/MDd，然后将当前配置改为release，配置属性-连接器-输入，右边附加依赖项添加cblas_d.lib和gsl_d.lib,配置属性-c++代码生成-运行库时改为/MD,到这一步，gsl库的配置便完成了。