- 

- 数学公式
  $$
  xyz+x^4+x_1
  $$

  $$
  V_{\mbox{你好}}
  $$

  $$
  \underline{x+y}
  $$

  

$$
PICC\tag{11}
$$

$$
\overbrace{x+y}+\underbrace{x-y}\tag*{1}
$$




$$
\Gamma(z) = \int_0^\infty t^{z-1}e^{-t}dt\,.
$$

$$
\binom{n+1}{2k}
$$


$$
f(\mathbf{x})=\mathbf{w}^T\mathbf{x}\tag{向量}
$$


$$
y=
\begin{cases}
-x,\quad x\leq 0\\
x, \quad x>0
\end{cases}
\tag{1}
$$

$$
\left\{ 
\begin{array}{c}
    a_1x+b_1y+c_1z=d_1 \\ 
    a_2x+b_2y+c_2z=d_2 \\ 
    a_3x+b_3y+c_3z=d_3
\end{array}
\right.
$$

$$
J(\theta) = \frac{1}{2m}\sum_{i = 0} ^m(y^i - h_\theta (x^i))^2
$$

$$
\frac{\partial J(\theta)}{\partial\theta_j}=-\frac1m\sum_{i=0}^m(y^i-h_\theta(x^i))x^i_j
$$

$$
a =
   \begin{cases}
     \int x\, \mathrm{d} x\\
     b^2
   \end{cases}
$$

$$
\begin{aligned}
 \boxed{x^2+y^2 = z^2}
\end{aligned}
$$

$$
\begin{gathered}
\operatorname{arg\,max}_a f(a) 
 = \operatorname*{arg\,max}_b f(b) \\
 \operatorname{arg\,min}_c f(c) 
 = \operatorname*{arg\,min}_d f(d)
\end{gathered}
$$

$$
\begin{aligned}
  \lim_{a\to \infty} \tfrac{1}{a}
\end{aligned}
$$

$$
\begin{aligned}
   \lim\nolimits_{a\to \infty} \tfrac{1}{a}
\end{aligned}
$$

$$
\begin{aligned}
   \int_a^b x^2  \mathrm{d} x
\end{aligned}2
$$

$$
\begin{aligned}
   \int\limits_a^b x^2  \mathrm{d} x
\end{aligned}
$$

$$
\begin{aligned}
J(\mathbf{w})&=\frac{1}{2m}\sum_{i=1}^m(f(\mathbf{x_i})-y_i)^2\\
&=\frac{1}{2m}\sum_{i=1}^m [f(\mathbf{x_i})]^2-2f(\mathbf{x_i)}y_i+y_i^2
\end{aligned}
$$

常见公式环境

| 环境名称 | 释义             |
| -------- | ---------------- |
| align    | 最基本的对齐环境 |
| multline | 非对齐环境       |
| gather   | 无对齐的连续方程 |

gathered 允许多行（多组）方程式在彼此之下设置并分配单个方程式编号
split 与align *类似，但在另一个显示的数学环境中使用
aligned 与align类似，可以在其他数学环境中使用。
alignedat 与alignat类似，同样需要一个额外的参数来指定要设置的方程列数。

如果各个方程需要在某个字符处对齐（如等号对齐），只需在所有要对齐的字符前加上 `&` 符号
$$
\begin{aligned}
J(\mathbf{θ})=-\frac{1}{m}∑_{i=1}^{m}y_ilogh_θ(x_i)+(1−y_i)log(1−h_θ(x_i))
\end{aligned}
$$

$$
\begin{aligned}
 \left.\begin{aligned}
        B'&=-\partial \times E,\\         %加&指定对齐位置
        E'&=\partial \times B - 4\pi j,
       \end{aligned}
 \right\}								%加右}
 \qquad \text{Maxwell's equations}
\end{aligned}
$$

$$
\begin{aligned}
 \sigma_1 &= x + y  &\quad \sigma_2 &= \frac{x}{y} \\	
 \sigma_1' &= \frac{\partial x + y}{\partial x} & \sigma_2' 
    &= \frac{\partial \frac{x}{y}}{\partial x}
\end{aligned}
$$

$$
\begin{aligned}
a_n&=\frac{1}{\pi}\int\limits_{-\pi}^{\pi}f(x)\cos nx\,\mathrm{d}x\\
&=\frac{1}{\pi}\int\limits_{-\pi}^{\pi}x^2\cos nx\,\mathrm{d}x\\[6pt]
\end{aligned}
$$

$$
\begin{pmatrix}1 & 2 \\ 3 &4\\ \end{pmatrix}
$$

$$
\begin{bmatrix}1 & 2 \\ 3 & 4\\ \end{bmatrix}
$$

$$
\begin{Bmatrix}1 &2 \\ 3 & 4\\ \end{Bmatrix}
$$

$$
\begin{vmatrix}1 &2 \\ 3 &4\\ \end{vmatrix}
$$

$$
\begin{Vmatrix}1 &  2 \\ 3 &  4\\ \end{Vmatrix}
$$

$$
\begin{pmatrix}1&a_1&a_1^2&\cdots&a_1^n\\1&a_2&a_2^2&\cdots&a_2^n\\\vdots&\vdots&\vdots&\ddots&\vdots\\1&a_m&a_m^2&\cdots&a_m^n\\\end{pmatrix}
$$

元素省略可以使用`\cdots` 表示⋯，`\ddots`表示⋱ ，`\vdots`表示⋮ ，从而省略矩阵中的元素，如：
$$
\begin{matrix}
1 & 2 & 3\\
4 & 5 & 6 \\
7 & 8 & 9
\end{matrix}
\tag{1}
$$

$$
\left[
\begin{array}{c|cc}
1 & 2 & 3 \\ \hline
4 & 5 & 6 \\
7 & 8 & 9
\end{array}
\right]
\tag{6}
$$

$$
x=a_0 + \frac{1^2}{a_ 1+\frac{2^2}{a_2+\frac{3^2}{a_3+ \frac{4^2}{a_4+...}}}}
$$

$$
x=a_0 + \cfrac{1^2}{a_ 1+\cfrac{2^2}{a_2+\cfrac{3^2}{a_3+ \cfrac{4^2}{a_4+...}}}}
$$

$$
a \equiv b \pmod n
$$

