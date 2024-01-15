# Hw0

### 作业说明

1. Eigen库(eigen.tuxfamily.org)
2. Eigen的矩阵与向量(https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html)

### 作业描述

给定一个点P=(2,1),将该点绕原点先逆时针旋转45$\degree$，再平移(1,2),计算出变换后点的坐标（要求用齐次坐标进行计算）。


点的齐次坐标:

$$
\left[
 \begin{matrix}
   x\\
   y\\
   1
  \end{matrix}
  \right]
$$


仿射变换的齐次坐标表示(先旋转，后平移):

$$
\left[
 \begin{matrix}
   a & b & t_x\\
   c & d & t_y\\
   0 & 0 & 1
  \end{matrix}
  \right]
$$
