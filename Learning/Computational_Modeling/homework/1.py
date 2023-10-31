import sympy as sp

a = sp.Rational(1, 2)
b = sp.Rational(1, 8)
c = sp.Rational(3, 8)

P = sp.Matrix([[a, b, c], [c, a, b], [b, c, a]])

eigenvalues = P.eigenvals()
eigenvectors = P.eigenvects()

print("特征值：", eigenvalues)
print("特征向量：", eigenvectors)
