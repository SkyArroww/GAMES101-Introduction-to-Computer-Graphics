# Hw3

### 作业描述

1. 修改rasterize_triangle(const Triangle& t) in rasterizer.cpp:在此处实现与作业2类似的插值算法，实现法向量、颜色、纹理颜色的插值。
2. 修改函数get_projection_matrix() in main.cpp:将你自己在之的的实验中实现的投影矩阵填到此处，此时你可以运行./Rasterizer output.png normal来观察法向量实现结果。
3. 修改函数phong_fragment_shader()in main.cpp:实现Blinn-Phong模型计算Fragment Color。
4. 修改函数texture_fragment_shader()in main.cpp:在实现Blinn-Phong的基础上，将纹理颜色视为公式中的kd，实现Texture Shading Fragment Shader。
5. 修改函数bump_fragment_shader()in main.cpp:在实现Blinn-Phong的基础上，仔细阅读该函数中的注释，实现Bump mapping
6. 修改函数displacement_fragment_shader()in main.cpp:在实现Bump mapping的基础上，实现displacement mapping.
7. [Bonus]双线性纹理插值:使用双线性插值进行纹理采样,在Texture
   类中实现一个新方法Vector3f getColorBilinear(float u, float v)并通过fragment shader调用它。为了使双线性插值的效果更加明显，你应该考虑选择更小的纹理图。请同时提交纹理插值与双线性纹理插值的结果，并进行比较。


### Solution

1. 计算重心坐标的$\alpha,\beta,\gamma$：
2.
