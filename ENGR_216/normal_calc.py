import scipy.stats as stats
# find area of -inf to z using z=1
area = stats.norm.cdf(-1.88)
print(f"Area between z = -1.78 and z = 2.43: {area:.4f}")
# find area of -z to z using z=1
# print(norm.cdf(1) - norm.cdf(-1))
# find z for area -inf to z using area=0.5
# print(norm.ppf(0.5))
# # find z for area -z to z using area=0.5
# p = 0.5
# alpha = 1 - p
# print(norm.ppf(1 - alpha / 2))
