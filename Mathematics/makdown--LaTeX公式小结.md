# makdown--LaTeX公式小结

## 数学公式

| 公式                  | Markdown            | 公式                   | Markdown                 |
| ------------------- | ------------------- | -------------------- | ------------------------ |
| 行间公式                | \$表达式\$             | $a\:b$               | a\:b                     |
| 块公式                 | \$\$表达式\$\$         | $a\;b$               | a\;b                     |
| $^{ab}A^{cd}$       | ^{ab}A^{cd}         | $a\!b$               | a\\!b                    |
| $_{ab}B_{cd}$       | \_{ab}B\_{cd}       | $a\,b$               | a\,b                     |
| $\frac{ab}{cd}$     | \frac{ab}{cd}       | $ab$                 | ab                       |
| $\sqrt{a+b}$        | \sqrt{a+b}          | $\overline{ab}$      | \overline{ab}            |
| $ \sqrt[c]{a+b}$    | \sqrt[c]{a+b}       | $\underline{ab}$     | \underline{ab}           |
| $\overbrace{ab}$    | \overbrace{ab}      | $a'$                 | a'                       |
| $\underbrace{ab}$   | \underbrace{ab}     | $a\prime$            | a\prime                  |
| $\cdots$            | \cdots              | $a^{\prime}$         | a^{\prime}               |
| $\ddots$            | \ddots              | $\ldots$             | \ldots                   |
| $\vdots$            | \vdots              | $$\lim_{a \to 0}xy$$ | \$\$\lim_{a \to 0}xy\$\$ |
| $$a+b=c \tag{1.1}$$ | a+b=c   \tag{1.1}   | $\lim_{a\to 0}xy$    | \$\lim_{a \to 0}xy\$     |
| $\sum^{a}_{b}$      | \$\sum^{a}_{b}\$    | $\vec X$             | \vec{X}                  |
| $$\sum^{a}_{b}$$    | \$$\sum^{a}_{b}\$\$ | $\mathbf{X}$         | \$\mathbf{X}\$           |



##自定义命令
命令\newcommand可以用来定义自己个性的命令。
例如一般矢量使用加粗的斜体表示，但是latex公式使用\mathbf{X}可以加粗，但不是斜体，那么自定义一个命令\vect，$\newcommand{\vect}[1]{\boldsymbol{#1}}$
```
$\newcommand{\vect}[1]{\boldsymbol{#1}}$
```
其中[1]表示要修饰一个表达式，{#1}表示要操作的表达式。那么定义上述命令之后，用\vect修饰字符的结果就是加粗的斜体，
例如而`\mathbf{X}`显示为$\mathbf{X}$，只加粗，而不是斜体。而`$vect{X}`显示为$\vect  {X}$，加粗的斜体。
再定义命令\SES

```
$ \newcommand{\SES}[3]{ 0 \to #1 \to #2 \to #3 \to 0 } $
```
$ \newcommand{\SES}[3]{ 0 \to #1 \to #2 \to #3 \to 0 } $
其中[3]表示要修饰3个表达式，{#1}表示要操作的第一个表达式
那么
```
$$ \SES {A}{B}{C} $$
```
显示为
$$
\SES {A}{B}{C}
$$

## 矩阵

块公式--简单矩阵

```
$$
\begein{matrix}
1 & 2 & 3 \\
a & b & c \\
4 & 5 & 6 
\end{matrix} \tag{1}
$$
```

$$
\begin{matrix}
1 & 2 & 3 \\
a & b & c \\
4 & 5 & 6 
\end{matrix} \tag{1}
$$

行间公式--简单矩阵

```
行间矩阵：$ \begin{matrix} 1 & 2  \\ a & b  \end{matrix}$
```



行间矩阵：$ \begin{matrix} 1 & 2  \\ a & b   \end{matrix} $

带{...}的矩阵

``` \left\{ \begin{matrix}   1 &amp;amp;amp; 2 &amp;amp;amp; 3 \\   4 &amp;amp;amp; 5 &amp;amp;amp; 6 \\   7 &amp;amp;amp; 8 &amp;amp;amp; 9  \end{matrix}  \right\} \tag{2}
$$
 \left\{
 \begin{matrix}
   1 & 2 & 3 \\
   4 & 5 & 6 \\
   7 & 8 & 9
  \end{matrix}
  \right\} \tag{2}
$$
```

结果
$$
\left\{
 \begin{matrix}
   1 & 2 & 3 \\
   4 & 5 & 6 \\
   7 & 8 & 9
  \end{matrix}
  \right\} \tag{2}
$$
带[...]的矩阵

```
$$
 \left[
 \begin{matrix}
   1 & 2 & 3 \\
   4 & 5 & 6 \\
   7 & 8 & 9
  \end{matrix}
  \right] \tag{3}
$$
```

结果
$$
\left[
 \begin{matrix}
   1 & 2 & 3 \\
   4 & 5 & 6 \\
   7 & 8 & 9
  \end{matrix}
  \right] \tag{3}
$$
带省略号的矩阵

```
$$
\left[
\begin{matrix}
 1      & 2      & \cdots & 4      \\
 7      & 6      & \cdots & 5      \\
 \vdots & \vdots & \ddots & \vdots \\
 8      & 9      & \cdots & 0      \\
\end{matrix}
\right]
$$
```

结果：
$$
\left[
\begin{matrix}
 1      & 2      & \cdots & 4      \\
 7      & 6      & \cdots & 5      \\
 \vdots & \vdots & \ddots & \vdots \\
 8      & 9      & \cdots & 0      \\
\end{matrix}
\right]
$$
带参数的矩阵,比如写增广矩阵

```
$$ 
\left[
    \begin{array}{cc|c}
      1 & 2 & 3 \\
      4 & 5 & 6
    \end{array}
\right] \tag{7}
$$
```

$$
\left[
    \begin{array}{cc|c}
      1 & 2 & 3 \\
      4 & 5 & 6
    \end{array}
\right] \tag{7}
$$



## 常用数学符号及希腊字母

| 大写         | markdown | 小写            | markdown    |
| ---------- | -------- | ------------- | ----------- |
| $A$        | A        | $\alpha$      | \alpha      |
| $B$        | B        | $\beta$       | \beta       |
| $\Gamma$   | \Gamma   | $\gamma$      | \gamma      |
| $\Delta$   | \Delta   | $\delta$      | \delta      |
| $E$        | E        | $\epsilon$    | \epsilon    |
|            |          | $\varepsilon$ | \varepsilon |
| $Z$        | Z        | $\zeta$       | \zeta       |
| $H$        | H        | $\eta$        | \eta        |
| $\Theta$   | \Theta   | $\theta$      | \theta      |
| $I$        | I        | $\iota$       | \iota       |
| $K$        | K        | $\kappa$      | \kappa      |
| $\Lambda$  | \Lambda  | $\lambda$     | \lambda     |
| $M$        | M        | $\mu$         | \mu         |
| $N$        | N        | $\nu$         | \nu         |
| $\Xi$      | \Xi      | $\xi$         | \xi         |
| $O$        | O        | $\omicron$    | \omicron    |
| $\Pi$      | \Pi      | $\pi$         | \pi         |
| $P$        | P        | $\rho$        | \rho        |
| $\Sigma$   | \Sigma   | $\sigma$      | \sigma      |
| $T$        | T        | $\tau$        | \tau        |
| $\Upsilon$ | \Upsilon | $\upsilon$    | \upsilon    |
| $\Phi$     | \Phi     | $\phi$        | \phi        |
|            |          | $\varphi$     | \varphi     |
| $X$        | X        | $\chi$        | \chi        |
| $\Psi$     | \Psi     | $\psi$        | \psi        |
| $\Omega$   | \Omega   | $\omega$      | \omega      |

## 数学运算符

![Binary Operation Symbols](image/Binary Operation Symbols.png)



## 关系运算符

![Relation Symbols](image/Relation Symbols.png)

## 标点符号

![Punctuation Symbols](image/Punctuation Symbols.png)

## 杂项符号

![](image/Miscellaneous Symbols.png)

## 可变大小的符号

![Variable-sized Symbols](image/Variable-sized Symbols.png)

## 三角函数等类log符号

![Log-like Symbols](image/Log-like Symbols.png)

## 分隔符

![Delimiters](image/Delimiters.png)

## 大分隔符

![Large delimiters](image/Large delimiters.png)

## 数学读音符号

![Math mode accents](image/Math mode accents.png)

## 其他一些构造符

![Sone other constructions](image/Some other constructions.png)