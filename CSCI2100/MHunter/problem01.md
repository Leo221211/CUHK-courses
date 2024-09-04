# 问题一：斜面海底的测量条带覆盖宽度与相邻两测量条带重合率模型

## 问题重述

在一片中心深度为$D_0$m，坡度为$\alpha$ rad.的斜面海底的海域内，测绘船以$\theta$°的多波束换能器开角沿垂直于海底地形负梯度方向、与中心距离$l$的测线进行测绘。如何描述测量条带覆盖宽度$W$、相邻两测量条带的重合率$\eta$与测线下方深度$D_k$(m)、测线间距$d$(m)及海底地形坡度$\alpha$ (rad.)的关系？  

## 问题分析

假设此海域西深东浅，海底坡度恒为$\alpha$，则海底地形的负梯度方向恒向东（右）侧。

称位于中心东侧，与中心所在铅垂线距离为$n d$的测线为第$n$条测线；称位于中心西侧与中心所在铅垂线距离为$m d$的测线为第$-m$条测线。例如，位于中心上方的测线与中心所在铅垂线相交，故称为第$0$条测线；当$d=200$时，位于中心西侧，与中心所在铅垂线距离$400$m的测线为第$-2$条测线。

对于第$n$条测线，称第$n-1$条测线为`上一条测线`；称第$n+1$条测线为`下一条测线`。

因为测线方向与海底地形负梯度方向垂直，沿测线方向海水深度变化率为0，故单一测线沿线海水深度为一定值。令第$k$条测线下的海水深度恒为$D_k$。

## 问题的建模及计算

### 海水深度的建模

对于给定的整数$k$，$D_k$与$\alpha$以及$D_0$的关系存在如图1的几何描述。（图1中k为负，故第k条测线在第0条测线的左侧）

<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);"
    src="1.1.PNG">
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">图1</div>
</center>

令$OA=D_0$，$O'B=D_k$ 则有：

$$ D_k = D_0 - k d \tan{\alpha} \qquad\qquad 1.1$$

### 测量条带宽度的建模

测绘船沿第$k$条测线测绘时，以测绘船所在铅垂线与海底平面的交点为原点，正东方向为x轴，竖直向上为y轴建立坐标系，则多波束换能器信号覆盖范围的边界与该坐标系平面相交于$OB$、$OC$二线段。如图2。

<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);"
    src="1.2.PNG">
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">图2</div>
</center>

此时，线段BC被信号范围所覆盖。如2.1式，该线段的水平跨度为第$k$条测线对应的测量条带宽度$W_k$。

$$ W_k= x_B-x_C\qquad\qquad 2.1$$

海底平面与坐标系平面交于直线$BC$，其斜截式为$y=x \times \tan{\alpha}$；

东侧的信号覆盖范围边界$AB$所在的直线满足斜截式$y=D_k - x \times \cot{\frac{\theta}{2}}$；

西侧信号覆盖范围边界$AC$所在的直线满足斜截式$y=D_k + x \times \cot{\frac{\theta}{2}}$；

联立$BC$与$AB$之斜截式可得：

$$ x_B \times \tan{\alpha} = D_k - x_B \times \cot{\frac{\theta}{2}} $$

解得：

$$x_B = \frac{D_k}{\tan{\alpha} + \cot{\frac{\theta}{2}}} \qquad \qquad 2.2$$

类似地：

$$ x_C \times \tan{\alpha} = D_k + x_C \times \cot{\frac{\theta}{2}} $$

解得：

$$x_C = \frac{D_k}{\tan{\alpha} - \cot{\frac{\theta}{2}}} \qquad \qquad 2.3$$

又由2.1得：

$$W_k = \frac{D_k}{\tan{\alpha} + \cot{\frac{\theta}{2}}} - \frac{D_k}{\tan{\alpha} - \cot{\frac{\theta}{2}}} $$

$$W_k = \frac{2 D_k \cot{\frac{\theta}{2}}}{\cot^2{\frac{\theta}{2}} - \tan^2{\alpha}} \qquad \qquad 2.4$$

### 相邻条带重叠率建模

设第$k$条测线对应的测量条带与其上一条测线所对应测量条带的重合率为$\eta_k$。

据上文所述，第$k$条测线与第$k-1$ 条测线的间距恒为$d$。对于$k-1$条测线建立类似图2的坐标系

