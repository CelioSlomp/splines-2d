# The Continuity of Splines

* Link: https://www.youtube.com/watch?v=jvPPXbo87ds

---

The project aims to develop a map for a follow line robot group of Instituto Federal Catarinense - Campus Blumenau. So, I need to use splines to determine the curves of the path.

---

### Linear Interpolation - Lerp

Imagine to points $P_0$ and $P_1$ that are connected by a line. So, we can find any point between these two with $P(t)$ by the formula $P(t) = (1-t)P_0 + tP_1$.

By adding anothers two points, we can calculate a smoother curve by doing the Lerp with the other two points, like the image:

![image](imagens/image.png)

This method is expensive. There are other ways to do that, like Catmull-Rom, uniform, etc.

---

### Catmull-Rom

$$
P(t) = \frac{1}{2}\cdot[1, t,t^2, t^3]\cdot \begin{bmatrix} 0&2 &0 &0 \\ -1& 0 &1 &0 \\ 2&-5  &4 &-1\\ -1&3  &-3 &1 \end{bmatrix}\cdot \begin{bmatrix} P_0\\P_1 \\P_2 \\P_3\end{bmatrix}
$$


---

### Cubic Spline

Has a $C^2$ continuity.

So we have that:
* $a = t_0 < t_1 < \dots < t_N = b$;
* $S''_i(x) = \alpha x + \beta$.

We denote that $S''_i(t_i) = z_i$ and $S''_i(t_{i+1}) = z_{i+1}$:
$$
S''_i(t_i) = z_i = \alpha t_i + \beta
$$
$$
S''_i(t_{i+1}) = z_{i+1} = \alpha t_{i+1} + \beta
$$
Applying $S''_i(t_{i+1}) - S''_i(t_i)$, we get:


* $h_i = t_{i+1} - t_i$;
* $\alpha = \frac{z_{i+1} - z_i}{h_i}$;
* $\beta = \frac{z_{i}t_{i+1} - z_{i+1}t_i}{h_i}$.

Going back to $S''_i(x)$:
$$
S''_i(x) = \frac{z_i}{h_i}(t_{i+1} - x) + \frac{z_{i+1}}{h_i}(x-t_i).
$$ 
Integrating:
$$
S'_i(x) = -\frac{z_i}{2h_i}(t_{i+1} - x)^2 + \frac{z_{i+1}}{2h_i}(x-t_i)^2 + p.
$$ 
Integrating one more time:
$$
S_i(x) = -\frac{z_i}{6h_i}(t_{i+1} - x)^3 + \frac{z_{i+1}}{6h_i}(x-t_i)^3 + px + q.
$$
We will change $p$ and $q$ by $C$ and $D$:
$$
S_i(x) = -\frac{z_i}{6h_i}(t_{i+1} - x)^3 + \frac{z_{i+1}}{6h_i}(x-t_i)^3 + C(x-t_i) + D(t_{i+1}-x).
$$




---

### Continuity

Lerp can't go to every point of the line, so we have to add some control points that will make sure the line will go through the joins.

We have that
$$
P(t) = [matrix 1x4][matrix 4x4][Points],
$$
then, deriving the $[matrix 1x4]$, we have the velocity, acceleration and then the joint. To make the velocity continuous (without jumps), we have to mirror the tangent points of the control points.

![image](imagens/fotopontos.png)

---

It will probably be enough until the minute 40 of the video. I'm going to implement something for that.