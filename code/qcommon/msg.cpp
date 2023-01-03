
#include "../game/q_shared.h"
#include "qcommon.h"





// Fast Huffman decoder/encoder from:
// from: https://github.com/mightycow/uberdemotools/commit/685b132abc4803f4c813fa07928cd9a4099e5d59
static const uint16_t HuffmanDecoderTable[2048] =
{
	2512, 2182, 512, 2763, 1859, 2808, 512, 2360, 1918, 1988, 512, 1803, 2158, 2358, 512, 2180,
	1798, 2053, 512, 1804, 2603, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2767, 512, 1664,
	1731, 2116, 512, 2788, 1791, 1808, 512, 1840, 2153, 1921, 512, 2708, 2723, 1549, 512, 2046,
	1893, 2717, 512, 2602, 1801, 1288, 512, 1568, 2480, 2062, 512, 1281, 2145, 2711, 512, 1543,
	1909, 2150, 512, 2077, 2338, 2762, 512, 2162, 1794, 2024, 512, 2168, 1922, 2447, 512, 2334,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2321, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2729, 512, 2633, 1791, 1919, 512, 2184, 1917, 1802, 512, 2710, 1795, 1549, 512, 2172,
	2375, 2789, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2374, 2446, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2751, 512, 2413,
	1798, 2529, 512, 1804, 2344, 1288, 512, 2404, 2156, 2786, 512, 1281, 1640, 2641, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2395, 1921, 512, 2586, 2319, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2773, 512, 1281, 2365, 2410, 512, 1543,
	1909, 2781, 512, 2097, 2411, 2740, 512, 2396, 1794, 2024, 512, 2734, 1922, 2733, 512, 2112,
	1857, 2528, 512, 2593, 2079, 1288, 512, 2648, 2143, 1908, 512, 1281, 1640, 2770, 512, 1664,
	1731, 2169, 512, 2714, 1791, 1919, 512, 2185, 1917, 1802, 512, 2398, 1795, 1549, 512, 2098,
	2801, 2361, 512, 2400, 2328, 1288, 512, 1568, 2783, 2713, 512, 1281, 1858, 1923, 512, 1543,
	2816, 2182, 512, 2497, 1859, 2397, 512, 2794, 1918, 1988, 512, 1803, 2158, 2772, 512, 2180,
	1798, 2053, 512, 1804, 2464, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2764, 512, 1664,
	1731, 2116, 512, 2620, 1791, 1808, 512, 1840, 2153, 1921, 512, 2716, 2384, 1549, 512, 2046,
	1893, 2448, 512, 2722, 1801, 1288, 512, 1568, 2472, 2062, 512, 1281, 2145, 2376, 512, 1543,
	1909, 2150, 512, 2077, 2366, 2709, 512, 2162, 1794, 2024, 512, 2168, 1922, 2735, 512, 2407,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2779, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2359, 512, 2705, 1791, 1919, 512, 2184, 1917, 1802, 512, 2642, 1795, 1549, 512, 2172,
	2394, 2645, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2450, 2771, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2585, 512, 2403,
	1798, 2619, 512, 1804, 2777, 1288, 512, 2355, 2156, 2362, 512, 1281, 1640, 2380, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2811, 1921, 512, 2402, 2601, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2719, 512, 1281, 2747, 2776, 512, 1543,
	1909, 2725, 512, 2097, 2445, 2765, 512, 2638, 1794, 2024, 512, 2444, 1922, 2774, 512, 2112,
	1857, 2727, 512, 2644, 2079, 1288, 512, 2800, 2143, 1908, 512, 1281, 1640, 2580, 512, 1664,
	1731, 2169, 512, 2646, 1791, 1919, 512, 2185, 1917, 1802, 512, 2588, 1795, 1549, 512, 2098,
	2322, 2504, 512, 2623, 2350, 1288, 512, 1568, 2323, 2721, 512, 1281, 1858, 1923, 512, 1543,
	2512, 2182, 512, 2746, 1859, 2798, 512, 2360, 1918, 1988, 512, 1803, 2158, 2358, 512, 2180,
	1798, 2053, 512, 1804, 2745, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2806, 512, 1664,
	1731, 2116, 512, 2796, 1791, 1808, 512, 1840, 2153, 1921, 512, 2582, 2761, 1549, 512, 2046,
	1893, 2793, 512, 2647, 1801, 1288, 512, 1568, 2480, 2062, 512, 1281, 2145, 2738, 512, 1543,
	1909, 2150, 512, 2077, 2338, 2715, 512, 2162, 1794, 2024, 512, 2168, 1922, 2447, 512, 2334,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2321, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2795, 512, 2750, 1791, 1919, 512, 2184, 1917, 1802, 512, 2732, 1795, 1549, 512, 2172,
	2375, 2604, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2374, 2446, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2813, 512, 2413,
	1798, 2529, 512, 1804, 2344, 1288, 512, 2404, 2156, 2743, 512, 1281, 1640, 2748, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2395, 1921, 512, 2637, 2319, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2812, 512, 1281, 2365, 2410, 512, 1543,
	1909, 2799, 512, 2097, 2411, 2802, 512, 2396, 1794, 2024, 512, 2649, 1922, 2595, 512, 2112,
	1857, 2528, 512, 2790, 2079, 1288, 512, 2634, 2143, 1908, 512, 1281, 1640, 2724, 512, 1664,
	1731, 2169, 512, 2730, 1791, 1919, 512, 2185, 1917, 1802, 512, 2398, 1795, 1549, 512, 2098,
	2605, 2361, 512, 2400, 2328, 1288, 512, 1568, 2787, 2810, 512, 1281, 1858, 1923, 512, 1543,
	2803, 2182, 512, 2497, 1859, 2397, 512, 2758, 1918, 1988, 512, 1803, 2158, 2598, 512, 2180,
	1798, 2053, 512, 1804, 2464, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2726, 512, 1664,
	1731, 2116, 512, 2583, 1791, 1808, 512, 1840, 2153, 1921, 512, 2712, 2384, 1549, 512, 2046,
	1893, 2448, 512, 2639, 1801, 1288, 512, 1568, 2472, 2062, 512, 1281, 2145, 2376, 512, 1543,
	1909, 2150, 512, 2077, 2366, 2731, 512, 2162, 1794, 2024, 512, 2168, 1922, 2766, 512, 2407,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2809, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2359, 512, 2587, 1791, 1919, 512, 2184, 1917, 1802, 512, 2643, 1795, 1549, 512, 2172,
	2394, 2635, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2450, 2749, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2778, 512, 2403,
	1798, 2791, 512, 1804, 2775, 1288, 512, 2355, 2156, 2362, 512, 1281, 1640, 2380, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2805, 1921, 512, 2402, 2741, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2769, 512, 1281, 2739, 2780, 512, 1543,
	1909, 2737, 512, 2097, 2445, 2596, 512, 2757, 1794, 2024, 512, 2444, 1922, 2599, 512, 2112,
	1857, 2804, 512, 2744, 2079, 1288, 512, 2707, 2143, 1908, 512, 1281, 1640, 2782, 512, 1664,
	1731, 2169, 512, 2742, 1791, 1919, 512, 2185, 1917, 1802, 512, 2718, 1795, 1549, 512, 2098,
	2322, 2504, 512, 2581, 2350, 1288, 512, 1568, 2323, 2597, 512, 1281, 1858, 1923, 512, 1543,
	2512, 2182, 512, 2763, 1859, 2808, 512, 2360, 1918, 1988, 512, 1803, 2158, 2358, 512, 2180,
	1798, 2053, 512, 1804, 2603, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2767, 512, 1664,
	1731, 2116, 512, 2788, 1791, 1808, 512, 1840, 2153, 1921, 512, 2708, 2723, 1549, 512, 2046,
	1893, 2717, 512, 2602, 1801, 1288, 512, 1568, 2480, 2062, 512, 1281, 2145, 2711, 512, 1543,
	1909, 2150, 512, 2077, 2338, 2762, 512, 2162, 1794, 2024, 512, 2168, 1922, 2447, 512, 2334,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2321, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2729, 512, 2633, 1791, 1919, 512, 2184, 1917, 1802, 512, 2710, 1795, 1549, 512, 2172,
	2375, 2789, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2374, 2446, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2751, 512, 2413,
	1798, 2529, 512, 1804, 2344, 1288, 512, 2404, 2156, 2786, 512, 1281, 1640, 2641, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2395, 1921, 512, 2586, 2319, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2773, 512, 1281, 2365, 2410, 512, 1543,
	1909, 2781, 512, 2097, 2411, 2740, 512, 2396, 1794, 2024, 512, 2734, 1922, 2733, 512, 2112,
	1857, 2528, 512, 2593, 2079, 1288, 512, 2648, 2143, 1908, 512, 1281, 1640, 2770, 512, 1664,
	1731, 2169, 512, 2714, 1791, 1919, 512, 2185, 1917, 1802, 512, 2398, 1795, 1549, 512, 2098,
	2801, 2361, 512, 2400, 2328, 1288, 512, 1568, 2783, 2713, 512, 1281, 1858, 1923, 512, 1543,
	3063, 2182, 512, 2497, 1859, 2397, 512, 2794, 1918, 1988, 512, 1803, 2158, 2772, 512, 2180,
	1798, 2053, 512, 1804, 2464, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2764, 512, 1664,
	1731, 2116, 512, 2620, 1791, 1808, 512, 1840, 2153, 1921, 512, 2716, 2384, 1549, 512, 2046,
	1893, 2448, 512, 2722, 1801, 1288, 512, 1568, 2472, 2062, 512, 1281, 2145, 2376, 512, 1543,
	1909, 2150, 512, 2077, 2366, 2709, 512, 2162, 1794, 2024, 512, 2168, 1922, 2735, 512, 2407,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2779, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2359, 512, 2705, 1791, 1919, 512, 2184, 1917, 1802, 512, 2642, 1795, 1549, 512, 2172,
	2394, 2645, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2450, 2771, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2585, 512, 2403,
	1798, 2619, 512, 1804, 2777, 1288, 512, 2355, 2156, 2362, 512, 1281, 1640, 2380, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2811, 1921, 512, 2402, 2601, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2719, 512, 1281, 2747, 2776, 512, 1543,
	1909, 2725, 512, 2097, 2445, 2765, 512, 2638, 1794, 2024, 512, 2444, 1922, 2774, 512, 2112,
	1857, 2727, 512, 2644, 2079, 1288, 512, 2800, 2143, 1908, 512, 1281, 1640, 2580, 512, 1664,
	1731, 2169, 512, 2646, 1791, 1919, 512, 2185, 1917, 1802, 512, 2588, 1795, 1549, 512, 2098,
	2322, 2504, 512, 2623, 2350, 1288, 512, 1568, 2323, 2721, 512, 1281, 1858, 1923, 512, 1543,
	2512, 2182, 512, 2746, 1859, 2798, 512, 2360, 1918, 1988, 512, 1803, 2158, 2358, 512, 2180,
	1798, 2053, 512, 1804, 2745, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2806, 512, 1664,
	1731, 2116, 512, 2796, 1791, 1808, 512, 1840, 2153, 1921, 512, 2582, 2761, 1549, 512, 2046,
	1893, 2793, 512, 2647, 1801, 1288, 512, 1568, 2480, 2062, 512, 1281, 2145, 2738, 512, 1543,
	1909, 2150, 512, 2077, 2338, 2715, 512, 2162, 1794, 2024, 512, 2168, 1922, 2447, 512, 2334,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2321, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2795, 512, 2750, 1791, 1919, 512, 2184, 1917, 1802, 512, 2732, 1795, 1549, 512, 2172,
	2375, 2604, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2374, 2446, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2813, 512, 2413,
	1798, 2529, 512, 1804, 2344, 1288, 512, 2404, 2156, 2743, 512, 1281, 1640, 2748, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2395, 1921, 512, 2637, 2319, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2812, 512, 1281, 2365, 2410, 512, 1543,
	1909, 2799, 512, 2097, 2411, 2802, 512, 2396, 1794, 2024, 512, 2649, 1922, 2595, 512, 2112,
	1857, 2528, 512, 2790, 2079, 1288, 512, 2634, 2143, 1908, 512, 1281, 1640, 2724, 512, 1664,
	1731, 2169, 512, 2730, 1791, 1919, 512, 2185, 1917, 1802, 512, 2398, 1795, 1549, 512, 2098,
	2605, 2361, 512, 2400, 2328, 1288, 512, 1568, 2787, 2810, 512, 1281, 1858, 1923, 512, 1543,
	2803, 2182, 512, 2497, 1859, 2397, 512, 2758, 1918, 1988, 512, 1803, 2158, 2598, 512, 2180,
	1798, 2053, 512, 1804, 2464, 1288, 512, 2166, 2285, 2167, 512, 1281, 1640, 2726, 512, 1664,
	1731, 2116, 512, 2583, 1791, 1808, 512, 1840, 2153, 1921, 512, 2712, 2384, 1549, 512, 2046,
	1893, 2448, 512, 2639, 1801, 1288, 512, 1568, 2472, 2062, 512, 1281, 2145, 2376, 512, 1543,
	1909, 2150, 512, 2077, 2366, 2731, 512, 2162, 1794, 2024, 512, 2168, 1922, 2766, 512, 2407,
	1857, 2117, 512, 2100, 2240, 1288, 512, 2186, 2809, 1908, 512, 1281, 1640, 2242, 512, 1664,
	1731, 2359, 512, 2587, 1791, 1919, 512, 2184, 1917, 1802, 512, 2643, 1795, 1549, 512, 2172,
	2394, 2635, 512, 2171, 2187, 1288, 512, 1568, 2095, 2163, 512, 1281, 1858, 1923, 512, 1543,
	2450, 2749, 512, 2181, 1859, 2160, 512, 2183, 1918, 1988, 512, 1803, 2161, 2778, 512, 2403,
	1798, 2791, 512, 1804, 2775, 1288, 512, 2355, 2156, 2362, 512, 1281, 1640, 2380, 512, 1664,
	1731, 2052, 512, 2170, 1791, 1808, 512, 1840, 2805, 1921, 512, 2402, 2741, 1549, 512, 2046,
	1893, 2101, 512, 2159, 1801, 1288, 512, 1568, 2247, 2769, 512, 1281, 2739, 2780, 512, 1543,
	1909, 2737, 512, 2097, 2445, 2596, 512, 2757, 1794, 2024, 512, 2444, 1922, 2599, 512, 2112,
	1857, 2804, 512, 2744, 2079, 1288, 512, 2707, 2143, 1908, 512, 1281, 1640, 2782, 512, 1664,
	1731, 2169, 512, 2742, 1791, 1919, 512, 2185, 1917, 1802, 512, 2718, 1795, 1549, 512, 2098,
	2322, 2504, 512, 2581, 2350, 1288, 512, 1568, 2323, 2597, 512, 1281, 1858, 1923, 512, 1543
};

static const uint16_t HuffmanEncoderTable[256] =
{
	34, 437, 1159, 1735, 2584, 280, 263, 1014, 341, 839, 1687, 183, 311, 726, 920, 2761,
	599, 1417, 7945, 8073, 7642, 16186, 8890, 12858, 3913, 6362, 2746, 13882, 7866, 1080, 1273, 3400,
	886, 3386, 1097, 11482, 15450, 16282, 12506, 15578, 2377, 6858, 826, 330, 10010, 12042, 8009, 1928,
	631, 3128, 3832, 6521, 1336, 2840, 217, 5657, 121, 3865, 6553, 6426, 4666, 3017, 5193, 7994,
	3320, 1287, 1991, 71, 536, 1304, 2057, 1801, 5081, 1594, 11642, 14106, 6617, 10938, 7290, 13114,
	4809, 2522, 5818, 14010, 7482, 5914, 7738, 9018, 3450, 11450, 5897, 2697, 3193, 4185, 3769, 3464,
	3897, 968, 6841, 6393, 2425, 775, 1048, 5369, 454, 648, 3033, 3145, 2440, 2297, 200, 2872,
	2136, 2248, 1144, 1944, 1431, 1031, 376, 408, 1208, 3608, 2616, 1848, 1784, 1671, 135, 1623,
	502, 663, 1223, 2007, 248, 2104, 24, 2168, 1656, 3704, 1400, 1864, 7353, 7241, 2073, 1241,
	4889, 5690, 6153, 15738, 698, 5210, 1722, 986, 12986, 3994, 3642, 9306, 4794, 794, 16058, 7066,
	4425, 8090, 4922, 714, 11738, 7194, 12762, 7450, 5001, 1562, 11834, 13402, 9914, 3290, 3258, 5338,
	905, 15386, 9178, 15306, 3162, 15050, 15930, 10650, 15674, 8522, 8250, 7114, 10714, 14362, 9786, 2266,
	1352, 4153, 1496, 518, 151, 15482, 12410, 2952, 7961, 8906, 1114, 58, 4570, 7258, 13530, 474,
	9, 15258, 3546, 6170, 4314, 2970, 7386, 14666, 7130, 6474, 14554, 5514, 15322, 3098, 15834, 3978,
	3353, 2329, 2458, 12170, 570, 1818, 11578, 14618, 1175, 8986, 4218, 9754, 8762, 392, 8282, 11290,
	7546, 3850, 11354, 12298, 15642, 14986, 8666, 20491, 90, 13706, 12186, 6794, 11162, 10458, 759, 582
};

static inline void HuffmanPutBitFast(uint8_t* fout, int32_t bitIndex, int32_t bit)
{
	const int32_t byteIndex = bitIndex >> 3;
	const int32_t bitOffset = bitIndex & 7;
	if (bitOffset == 0) // Is this the first bit of a new byte?
	{
		// We don't need to preserve what's already in there,
		// so we can write that byte immediately.
		fout[byteIndex] = (unsigned char)bit;
		return;
	}

	fout[(bitIndex >> 3)] |= bit << (bitIndex & 7);
}

static inline void HuffmanOffsetTransmitFast(uint8_t* fout, int32_t* offset, int32_t ch)
{
	const uint16_t result = HuffmanEncoderTable[ch];
	const uint16_t bitCount = result & 15;
	const uint16_t code = (result >> 4) & 0x7FF;
	const uint32_t bitIndex = *(const uint32_t*)offset;

	int32_t bits = (int32_t)code;
	for (uint32_t i = 0; i < bitCount; ++i)
	{
		HuffmanPutBitFast(fout, bitIndex + i, bits & 1);
		bits >>= 1;
	}

	*offset += (int32_t)bitCount;
}





/*
==============================================================================

			MESSAGE IO FUNCTIONS

Handles byte ordering and avoids alignment errors
==============================================================================
*/


void MSG_Init(msg_t* buf, byte* data, int length) {
	memset(buf, 0, sizeof(*buf));
	buf->data = data;
	buf->maxsize = length;
}


void MSG_InitOOB(msg_t* buf, byte* data, int length) {
	memset(buf, 0, sizeof(*buf));
	buf->data = data;
	buf->maxsize = length;
	buf->oob = qtrue;
}

void MSG_Clear( msg_t *buf ) {
	buf->cursize = 0;
	buf->overflowed = qfalse;
	buf->bit = 0;
}


void MSG_Bitstream(msg_t* buf) {
	buf->oob = qfalse;
}

void MSG_BeginReading(msg_t* msg) {
	msg->readcount = 0;
	msg->bit = 0;
	msg->oob = qfalse;
}

void MSG_BeginReadingOOB(msg_t* msg) {
	msg->readcount = 0;
	msg->bit = 0;
	msg->oob = qtrue;
}

/*
void MSG_ReadByteAlign( msg_t *buf ) {
	// round up to the next byte
	if ( buf->bit ) {
		buf->bit = 0;
		buf->readcount++;
	}
}

void *MSG_GetSpace( msg_t *buf, int length ) {
	void	*data;

	// round up to the next byte
	if ( buf->bit ) {
		buf->bit = 0;
		buf->cursize++;
	}

	if ( buf->cursize + length > buf->maxsize )	{
		if ( !buf->allowoverflow ) {
			Com_Error (ERR_FATAL, "MSG_GetSpace: overflow without allowoverflow set");
		}
		if ( length > buf->maxsize ) {
			Com_Error (ERR_FATAL, "MSG_GetSpace: %i is > full buffer size", length);
		}
		Com_Printf ("MSG_GetSpace: overflow\n");
		MSG_Clear (buf); 
		buf->overflowed = qtrue;
	}

	data = buf->data + buf->cursize;
	buf->cursize += length;
	
	return data;
}*/



/*
=============================================================================

bit functions
  
=============================================================================
*/

int	overflows;

// negative bit values include signs
void MSG_WriteBits(msg_t* msg, int value, int bits) {
	int	i;

	// this isn't an exact overflow check, but close enough
	if (msg->maxsize - msg->cursize < 4) {
		msg->overflowed = qtrue;
		return;
	}

	if (bits == 0 || bits < -31 || bits > 32) {
		Com_Error(ERR_DROP, "MSG_WriteBits: bad bits %i", bits);
	}

	// check for overflows
	if (bits != 32) {
		if (bits > 0) {
			if (value > ((1 << bits) - 1) || value < 0) {
				overflows++;
			}
		}
		else {
			int	r;

			r = 1 << (bits - 1);

			if (value > r - 1 || value < -r) {
				overflows++;
			}
		}
	}
	if (bits < 0) {
		bits = -bits;
	}
	// Special handling for new raw type of message (for better compression afterwards)
	if (msg->oob) {
		if (bits == 8) {
			msg->data[msg->cursize] = value;
			msg->cursize += 1;
			msg->bit += 8;
		}
		else if (bits == 16) {
			unsigned short* sp = (unsigned short*)&msg->data[msg->cursize];
			*sp = LittleShort(value);
			msg->cursize += 2;
			msg->bit += 16;
		}
		else if (bits == 32) {
			unsigned int* ip = (unsigned int*)&msg->data[msg->cursize];
			*ip = LittleLong(value);
			msg->cursize += 4;
			msg->bit += 8;
		}
		else {
			Com_Error(ERR_DROP, "can't read %d bits\n", bits);
		}
	}
	else {
		value &= (0xffffffff >> (32 - bits));
		if (bits & 7) {
			int nbits;
			nbits = bits & 7;
			for (i = 0; i < nbits; i++) {
				HuffmanPutBitFast(msg->data, msg->bit, (value & 1));
				value = (value >> 1);
				msg->bit++;
			}
			bits = bits - nbits;
		}
		if (bits) {
			for (i = 0; i < bits; i += 8) {
				HuffmanOffsetTransmitFast(msg->data, &msg->bit, (value & 0xff));
				value = (value >> 8);
			}
		}
		msg->cursize = (msg->bit >> 3) + 1;
	}
}

#ifdef MSG_READBITS_TRANSCODE
msg_t* transcodeTargetMsg = NULL;
#endif

int MSG_ReadBits(msg_t* msg, int bits) {
	int			value;
	int			get;
	qboolean	sgn;
	int			i, nbits;
	value = 0;

	if (bits < 0) {
		bits = -bits;
		sgn = qtrue;
	}
	else {
		sgn = qfalse;
	}

	if (msg->oob) {
		if (bits == 8) {
			value = msg->data[msg->readcount];
			msg->readcount += 1;
			msg->bit += 8;
		}
		else if (bits == 16) {
			unsigned short* sp = (unsigned short*)&msg->data[msg->readcount];
			value = LittleShort(*sp);
			msg->readcount += 2;
			msg->bit += 16;
		}
		else if (bits == 32) {
			unsigned int* ip = (unsigned int*)&msg->data[msg->readcount];
			value = LittleLong(*ip);
			msg->readcount += 4;
			msg->bit += 32;
		}
		else {
			Com_Error(ERR_DROP, "can't read %d bits\n", bits);
		}
	}
	else {

		// Fast Huffman decoder from:
		// from: https://github.com/mightycow/uberdemotools/commit/685b132abc4803f4c813fa07928cd9a4099e5d59
		const uint8_t* const bufferData = msg->data;
		const int32_t nbits = bits & 7;
		int32_t bitIndex = msg->bit;
		if (nbits)
		{
			const int16_t allBits = *(const int16_t*)(bufferData + (bitIndex >> 3)) >> (bitIndex & 7);
			value = allBits & ((1 << nbits) - 1);
			bitIndex += nbits;
			bits -= nbits;
		}

		if (bits)
		{
			for (int32_t i = 0; i < bits; i += 8)
			{
				const uint16_t code = ((*(const uint32_t*)(bufferData + (bitIndex >> 3))) >> ((uint32_t)bitIndex & 7)) & 0x7FF;
				const uint16_t entry = HuffmanDecoderTable[code];
				value |= (int32_t(entry & 0xFF) << (i + nbits));
				bitIndex += int32_t(entry >> 8);
			}
		}

		msg->bit = bitIndex;
		msg->readcount = (bitIndex >> 3) + 1;
	}
	if (sgn) {
		if (value & (1 << (bits - 1))) {
			value |= -1 ^ ((1 << bits) - 1);
		}
	}


	return value;
}



//================================================================================

//
// writing functions
//


void MSG_WriteChar(msg_t* sb, int c) {
#ifdef PARANOID
	if (c < -128 || c > 127)
		Com_Error(ERR_FATAL, "MSG_WriteChar: range error");
#endif

	MSG_WriteBits(sb, c, 8);
}

void MSG_WriteByte(msg_t* sb, int c) {
#ifdef PARANOID
	if (c < 0 || c > 255)
		Com_Error(ERR_FATAL, "MSG_WriteByte: range error");
#endif

	MSG_WriteBits(sb, c, 8);
}

void MSG_WriteData(msg_t* buf, const void* data, int length) {
	int i;
	for (i = 0; i < length; i++) {
		MSG_WriteByte(buf, ((byte*)data)[i]);
	}
}

void MSG_WriteShort(msg_t* sb, int c) {
#ifdef PARANOID
	if (c < ((short)0x8000) || c >(short)0x7fff)
		Com_Error(ERR_FATAL, "MSG_WriteShort: range error");
#endif

	MSG_WriteBits(sb, c, 16);
}
void MSG_WriteSShort(msg_t* sb, int c) {
#ifdef PARANOID
	if (c < ((short)0x8000) || c >(short)0x7fff)
		Com_Error(ERR_FATAL, "MSG_WriteShort: range error");
#endif

	MSG_WriteBits(sb, c, -16);
}

void MSG_WriteLong(msg_t* sb, int c) {
	MSG_WriteBits(sb, c, 32);
}

void MSG_WriteFloat(msg_t* sb, float f) {
	union {
		float	f;
		int	l;
	} dat;

	dat.f = f;
	MSG_WriteBits(sb, dat.l, 32);
}

void MSG_WriteString(msg_t* sb, const char* s) {
	if (!s) {
		MSG_WriteData(sb, "", 1);
	}
	else {
		int		l, i;
		char	string[MAX_STRING_CHARS];

		l = strlen(s);
		if (l >= MAX_STRING_CHARS) {
			Com_Printf("MSG_WriteString: MAX_STRING_CHARS");
			MSG_WriteData(sb, "", 1);
			return;
		}
		Q_strncpyz(string, s, sizeof(string));

		// get rid of 0xff chars, because old clients don't like them
		for (i = 0; i < l; i++) {
			if (((byte*)string)[i] > 127) {
				string[i] = '.';
			}
		}

		MSG_WriteData(sb, string, l + 1);
	}
}

void MSG_WriteAngle(msg_t* sb, float f) {
	MSG_WriteByte(sb, (int)(f * 256 / 360) & 255);
}

void MSG_WriteAngle16(msg_t* sb, float f) {
	MSG_WriteShort(sb, ANGLE2SHORT(f));
}

//============================================================

//
// reading functions
//

int MSG_ReadChar(msg_t* msg) {
	int	c;

	c = (signed char)MSG_ReadBits(msg, 8);
	if (msg->readcount > msg->cursize) {
		c = -1;
	}

	return c;
}

int MSG_ReadByte(msg_t* msg) {
	int	c;

	c = (unsigned char)MSG_ReadBits(msg, 8);
	if (msg->readcount > msg->cursize) {
		c = -1;
	}
	return c;
}

int MSG_ReadShort(msg_t* msg) {
	int	c;

	c = (short)MSG_ReadBits(msg, 16);
	if (msg->readcount > msg->cursize) {
		c = -1;
	}

	return c;
}

int MSG_ReadSShort(msg_t* msg) {
	int	c;

	c = (short)MSG_ReadBits(msg, -16);
	if (msg->readcount > msg->cursize) {
		c = -1;
	}

	return c;
}

int MSG_ReadLong(msg_t* msg) {
	int	c;

	c = MSG_ReadBits(msg, 32);
	if (msg->readcount > msg->cursize) {
		c = -1;
	}

	return c;
}

float MSG_ReadFloat(msg_t* msg) {
	union {
		byte	b[4];
		float	f;
		int	l;
	} dat;

	dat.l = MSG_ReadBits(msg, 32);
	if (msg->readcount > msg->cursize) {
		dat.f = -1;
	}

	return dat.f;
}

char* MSG_ReadString(msg_t* msg) {
	static char	string[MAX_STRING_CHARS];
	int		l, c;

	l = 0;
	do {
		c = MSG_ReadByte(msg);		// use ReadByte so -1 is out of bounds
		if (c == -1 || c == 0) {
			break;
		}
		// translate all fmt spec to avoid crash bugs
		if (c == '%') {
			c = '.';
		}
		// don't allow higher ascii values
		if (c > 127) {
			c = '.';
		}

		string[l] = c;
		l++;
	} while (l <= sizeof(string) - 1);

	// some bonus protection, shouldn't occur cause server doesn't write such things
	if (l <= sizeof(string) - 1)
	{
		string[l] = 0;
	}
	else
	{
		string[sizeof(string) - 1] = 0;
	}

	return string;
}


char* MSG_ReadStringLine(msg_t* msg) {
	static char	string[MAX_STRING_CHARS];
	int		l, c;

	l = 0;
	do {
		c = MSG_ReadByte(msg);		// use ReadByte so -1 is out of bounds
		if (c == -1 || c == 0 || c == '\n') {
			break;
		}
		// translate all fmt spec to avoid crash bugs
		if (c == '%') {
			c = '.';
		}
		string[l] = c;
		l++;
	} while (l < sizeof(string) - 1);

	string[l] = 0;

	return string;
}

float MSG_ReadAngle16(msg_t* msg) {
	return SHORT2ANGLE(MSG_ReadShort(msg));
}

void MSG_ReadData(msg_t* msg, void* data, int len) {
	int		i;

	for (i = 0; i < len; i++) {
		((byte*)data)[i] = MSG_ReadByte(msg);
	}
}


/*
=============================================================================

delta functions
  
=============================================================================
*/

extern cvar_t *cl_shownet;

#define	LOG(x) if( cl_shownet->integer == 4 ) { Com_Printf("%s ", x ); };

void MSG_WriteDelta( msg_t *msg, int oldV, int newV, int bits ) {
	if ( oldV == newV ) {
		MSG_WriteBits( msg, 0, 1 );
		return;
	}
	MSG_WriteBits( msg, 1, 1 );
	MSG_WriteBits( msg, newV, bits );
}

int	MSG_ReadDelta( msg_t *msg, int oldV, int bits ) {
	if ( MSG_ReadBits( msg, 1 ) ) {
		return MSG_ReadBits( msg, bits );
	}
	return oldV;
}

void MSG_WriteDeltaFloat( msg_t *msg, float oldV, float newV ) {
	if ( oldV == newV ) {
		MSG_WriteBits( msg, 0, 1 );
		return;
	}
	MSG_WriteBits( msg, 1, 1 );
	MSG_WriteBits( msg, *(int *)&newV, 32 );
}

float MSG_ReadDeltaFloat( msg_t *msg, float oldV ) {
	if ( MSG_ReadBits( msg, 1 ) ) {
		float	newV;

		*(int *)&newV = MSG_ReadBits( msg, 32 );
		return newV;
	}
	return oldV;
}


/*
============================================================================

usercmd_t communication

============================================================================
*/

// ms is allways sent, the others are optional
#define	CM_ANGLE1 	(1<<0)
#define	CM_ANGLE2 	(1<<1)
#define	CM_ANGLE3 	(1<<2)
#define	CM_FORWARD	(1<<3)
#define	CM_SIDE		(1<<4)
#define	CM_UP		(1<<5)
#define	CM_BUTTONS	(1<<6)
#define CM_WEAPON	(1<<7)

/*
=====================
MSG_WriteDeltaUsercmd
=====================
*/
void MSG_WriteDeltaUsercmd( msg_t *msg, usercmd_t *from, usercmd_t *to ) {
	MSG_WriteDelta( msg, from->serverTime, to->serverTime, 32 );
	MSG_WriteDelta( msg, from->angles[0], to->angles[0], 16 );
	MSG_WriteDelta( msg, from->angles[1], to->angles[1], 16 );
	MSG_WriteDelta( msg, from->angles[2], to->angles[2], 16 );
	MSG_WriteDelta( msg, from->forwardmove, to->forwardmove, -8 );
	MSG_WriteDelta( msg, from->rightmove, to->rightmove, -8 );
	MSG_WriteDelta( msg, from->upmove, to->upmove, -8 );
	MSG_WriteDelta( msg, from->buttons, to->buttons, 16 );//FIXME:  We're only really using 9 bits...can this be changed to that?
	MSG_WriteDelta( msg, from->weapon, to->weapon, 8 );
}


/*
=====================
MSG_ReadDeltaUsercmd
=====================
*/
void MSG_ReadDeltaUsercmd( msg_t *msg, usercmd_t *from, usercmd_t *to ) {
	to->serverTime = MSG_ReadDelta( msg, from->serverTime, 32);
	to->angles[0] = MSG_ReadDelta( msg, from->angles[0], 16);
	to->angles[1] = MSG_ReadDelta( msg, from->angles[1], 16);
	to->angles[2] = MSG_ReadDelta( msg, from->angles[2], 16);
	to->forwardmove = MSG_ReadDelta( msg, from->forwardmove, -8);
	to->rightmove = MSG_ReadDelta( msg, from->rightmove, -8);
	to->upmove = MSG_ReadDelta( msg, from->upmove, -8);
	to->buttons = MSG_ReadDelta( msg, from->buttons, 16);//FIXME:  We're only really using 9 bits...can this be changed to that?
	to->weapon = MSG_ReadDelta( msg, from->weapon, 8);
}

/*
=============================================================================

entityState_t communication
  
=============================================================================
*/

typedef struct {
	char	*name;
	int		offset;
	int		bits;		// 0 = float
} netField_t;

// using the stringizing operator to save typing...
#define	NETF(x) #x,(int)&((entityState_t*)0)->x

const netField_t	entityStateFields[] = 
{
{ NETF(eType), 8 },
{ NETF(eFlags), 32 },

{ NETF(pos.trType), 8 },
{ NETF(pos.trTime), 32 },
{ NETF(pos.trDuration), 32 },
{ NETF(pos.trBase[0]), 0 },
{ NETF(pos.trBase[1]), 0 },
{ NETF(pos.trBase[2]), 0 },
{ NETF(pos.trDelta[0]), 0 },
{ NETF(pos.trDelta[1]), 0 },
{ NETF(pos.trDelta[2]), 0 },

{ NETF(apos.trType), 8 },
{ NETF(apos.trTime), 32 },
{ NETF(apos.trDuration), 32 },
{ NETF(apos.trBase[0]), 0 },
{ NETF(apos.trBase[1]), 0 },
{ NETF(apos.trBase[2]), 0 },
{ NETF(apos.trDelta[0]), 0 },
{ NETF(apos.trDelta[1]), 0 },
{ NETF(apos.trDelta[2]), 0 },

{ NETF(time), 32 },
{ NETF(time2), 32 },

{ NETF(origin[0]), 0 },
{ NETF(origin[1]), 0 },
{ NETF(origin[2]), 0 },

{ NETF(origin2[0]), 0 },
{ NETF(origin2[1]), 0 },
{ NETF(origin2[2]), 0 },

{ NETF(angles[0]), 0 },
{ NETF(angles[1]), 0 },
{ NETF(angles[2]), 0 },

{ NETF(angles2[0]), 0 },
{ NETF(angles2[1]), 0 },
{ NETF(angles2[2]), 0 },

{ NETF(otherEntityNum), GENTITYNUM_BITS },
{ NETF(otherEntityNum2), GENTITYNUM_BITS },
{ NETF(groundEntityNum), GENTITYNUM_BITS },

{ NETF(constantLight), 32 },
{ NETF(loopSound), 16 },
{ NETF(modelindex), 9 },	//0 to 511
{ NETF(modelindex2), 8 },
{ NETF(modelindex3), 8 },
{ NETF(clientNum), 32 },
{ NETF(frame), 16 },

{ NETF(solid), 24 },

{ NETF(event), 10 },
{ NETF(eventParm), 16 },

{ NETF(powerups), 16 },
{ NETF(weapon), 8 },
{ NETF(legsAnim), 16 },
{ NETF(legsAnimTimer), 8 },
{ NETF(torsoAnim), 16 },
{ NETF(torsoAnimTimer), 8 },
{ NETF(scale), 8 },

{ NETF(saberInFlight), 4 },
{ NETF(saberActive), 4 },
{ NETF(vehicleModel), 32 },
/*
Ghoul2 Insert Start
*/
{ NETF(modelScale[0]), 0 },
{ NETF(modelScale[1]), 0 },
{ NETF(modelScale[2]), 0 },
{ NETF(radius), 16 },
{ NETF(boltInfo), 32 },
//{ NETF(ghoul2), 32 },


//loadsavecrash
//#if _DEBUG
//
//{ NETF(mins[0]), 0 },
//{ NETF(mins[1]), 0 },
//{ NETF(mins[2]), 0 },
//{ NETF(maxs[0]), 0 },
//{ NETF(maxs[1]), 0 },
//{ NETF(maxs[2]), 0 }
//#endif


};


// if (int)f == f and (int)f + ( 1<<(FLOAT_INT_BITS-1) ) < ( 1 << FLOAT_INT_BITS )
// the float will be sent with FLOAT_INT_BITS, otherwise all 32 bits will be sent
#define	FLOAT_INT_BITS	13
#define	FLOAT_INT_BIAS	(1<<(FLOAT_INT_BITS-1))

void MSG_WriteField (msg_t *msg, const int *toF, const netField_t *field)
{
	int			trunc;
	float		fullFloat;

	if ( field->bits == -1)
	{	// a -1 in the bits field means it's a float that's always between -1 and 1
		int temp = *(float *)toF * 32767;
 		MSG_WriteBits( msg, temp, -16 );
	}
	else
 	if ( field->bits == 0 ) {
 		// float
 		fullFloat = *(float *)toF;
 		trunc = (int)fullFloat;

		if (fullFloat == 0.0f) {
			MSG_WriteBits( msg, 0, 1 );	//it's a zero
		} else {
			MSG_WriteBits( msg, 1, 1 );	//not a zero
			if ( trunc == fullFloat && trunc + FLOAT_INT_BIAS >= 0 && 
				trunc + FLOAT_INT_BIAS < ( 1 << FLOAT_INT_BITS ) ) {
				// send as small integer
				MSG_WriteBits( msg, 0, 1 );
				MSG_WriteBits( msg, trunc + FLOAT_INT_BIAS, FLOAT_INT_BITS );
			} else {
				// send as full floating point value
				MSG_WriteBits( msg, 1, 1 );
				MSG_WriteBits( msg, *toF, 32 );
			}
		}
 	} else {
		if (*toF == 0) {
			MSG_WriteBits( msg, 0, 1 );	//it's a zero
		} else {
			MSG_WriteBits( msg, 1, 1 );	//not a zero
			// integer
			MSG_WriteBits( msg, *toF, field->bits );
		}
 	}
}

void MSG_ReadField (msg_t *msg, int *toF, const netField_t *field, int print)
{
	int			trunc;

	if ( field->bits == -1)
	{	// a -1 in the bits field means it's a float that's always between -1 and 1
		int temp = MSG_ReadBits( msg, -16);
		*(float *)toF = (float)temp / 32767;
	}
	else
  	if ( field->bits == 0 ) {
  		// float
		if ( MSG_ReadBits( msg, 1 ) == 0 ) {
				*(float *)toF = 0.0f; 
		} else {
			if ( MSG_ReadBits( msg, 1 ) == 0 ) {
				// integral float
				trunc = MSG_ReadBits( msg, FLOAT_INT_BITS );
				// bias to allow equal parts positive and negative
				trunc -= FLOAT_INT_BIAS;
				*(float *)toF = trunc; 
				if ( print ) {
					Com_Printf( "%s:%i ", field->name, trunc );
				}
			} else {
				// full floating point value
				*toF = MSG_ReadBits( msg, 32 );
				if ( print ) {
					Com_Printf( "%s:%f ", field->name, *(float *)toF );
				}
			}
		}
	} else {
		if ( MSG_ReadBits( msg, 1 ) == 0 ) {
			*toF = 0;
		} else {
			// integer
			*toF = MSG_ReadBits( msg, field->bits );
			if ( print ) {
				Com_Printf( "%s:%i ", field->name, *toF );
			}
		}
	}
}


/*
==================
MSG_WriteDeltaEntity


GENTITYNUM_BITS 1 : remove this entity
GENTITYNUM_BITS 0 1 SMALL_VECTOR_BITS <data>
GENTITYNUM_BITS 0 0 LARGE_VECTOR_BITS >data>

Writes part of a packetentities message, including the entity number.
Can delta from either a baseline or a previous packet_entity
If to is NULL, a remove entity update will be sent
If force is not set, then nothing at all will be generated if the entity is
identical, under the assumption that the in-order delta code will catch it.
==================
*/

void MSG_WriteDeltaEntity(msg_t* msg, struct entityState_s* from, struct entityState_s* to,
	qboolean force) {
	int			i, lc;
	int			numFields;
	const netField_t* field;
	int			trunc;
	float		fullFloat;
	int* fromF, * toF;

	numFields = sizeof(entityStateFields) / sizeof(entityStateFields[0]);

	// all fields should be 32 bits to avoid any compiler packing issues
	// the "number" field is not part of the field list
	// if this assert fails, someone added a field to the entityState_t
	// struct without updating the message fields
	assert(numFields + 1 == sizeof(*from) / 4);

	// a NULL to is a delta remove message
	if (to == NULL) {
		if (from == NULL) {
			return;
		}
		MSG_WriteBits(msg, from->number, GENTITYNUM_BITS);
		MSG_WriteBits(msg, 1, 1);
		return;
	}

	if (to->number < 0 || to->number >= MAX_GENTITIES) {
		Com_Error(ERR_FATAL, "MSG_WriteDeltaEntity: Bad entity number: %i", to->number);
	}

	lc = 0;
	// build the change vector as bytes so it is endien independent

	field = entityStateFields;

	for (i = 0; i < numFields; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);
		if (*fromF != *toF) {
			lc = i + 1;
		}
	}

	if (lc == 0) {
		// nothing at all changed
		if (!force) {
			return;		// nothing at all
		}
		// write two bits for no change
		MSG_WriteBits(msg, to->number, GENTITYNUM_BITS);
		MSG_WriteBits(msg, 0, 1);		// not removed
		MSG_WriteBits(msg, 0, 1);		// no delta
		return;
	}

	MSG_WriteBits(msg, to->number, GENTITYNUM_BITS);
	MSG_WriteBits(msg, 0, 1);			// not removed
	MSG_WriteBits(msg, 1, 1);			// we have a delta

	MSG_WriteByte(msg, lc);	// # of changes

	field = entityStateFields;

	for (i = 0; i < lc; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);

		if (*fromF == *toF) {
			MSG_WriteBits(msg, 0, 1);	// no change
			continue;
		}

		MSG_WriteBits(msg, 1, 1);	// changed

		if (field->bits == 0) {
			// float
			fullFloat = *(float*)toF;
			trunc = (int)fullFloat;

			if (fullFloat == 0.0f) {
				MSG_WriteBits(msg, 0, 1);
			}
			else {
				MSG_WriteBits(msg, 1, 1);
				if (trunc == fullFloat && trunc + FLOAT_INT_BIAS >= 0 &&
					trunc + FLOAT_INT_BIAS < (1 << FLOAT_INT_BITS)) {
					// send as small integer
					MSG_WriteBits(msg, 0, 1);
					MSG_WriteBits(msg, trunc + FLOAT_INT_BIAS, FLOAT_INT_BITS);
				}
				else {
					// send as full floating point value
					MSG_WriteBits(msg, 1, 1);
					MSG_WriteBits(msg, *toF, 32);
				}
			}
		}
		else {
			if (*toF == 0) {
				MSG_WriteBits(msg, 0, 1);
			}
			else {
				MSG_WriteBits(msg, 1, 1);
				// integer
				MSG_WriteBits(msg, *toF, field->bits);
			}
		}
	}

}


/*
==================
MSG_ReadDeltaEntity

The entity number has already been read from the message, which
is how the from state is identified.

If the delta removes the entity, entityState_t->number will be set to MAX_GENTITIES-1

Can go from either a baseline or a previous packet_entity
==================
*/
extern	cvar_t	*cl_shownet;

void MSG_ReadDeltaEntity(msg_t* msg, entityState_t* from, entityState_t* to,
	int number) {
	int			i, lc;
	int			numFields;
	const netField_t* field;
	int* fromF, * toF;
	int			print;
	int			trunc;
	int			startBit, endBit;

	if (number < 0 || number >= MAX_GENTITIES) {
		Com_Error(ERR_DROP, "Bad delta entity number: %i", number);
	}

	if (msg->bit == 0) {
		startBit = msg->readcount * 8 - GENTITYNUM_BITS;
	}
	else {
		startBit = (msg->readcount - 1) * 8 + msg->bit - GENTITYNUM_BITS;
	}

	// check for a remove
	if (MSG_ReadBits(msg, 1) == 1) {
		memset(to, 0, sizeof(*to));
		to->number = MAX_GENTITIES - 1;
		if (cl_shownet->integer >= 2 || cl_shownet->integer == -1) {
			Com_Printf("%3i: #%-3i remove\n", msg->readcount, number);
		}
		return;
	}

	// check for no delta
	if (MSG_ReadBits(msg, 1) == 0) {
		*to = *from;
		to->number = number;
		return;
	}

	numFields = sizeof(entityStateFields) / sizeof(entityStateFields[0]);

	lc = MSG_ReadByte(msg);

	// shownet 2/3 will interleave with other printed info, -1 will
	// just print the delta records`
	if (cl_shownet->integer >= 2 || cl_shownet->integer == -1) {
		print = 1;
		Com_Printf("%3i: #%-3i ", msg->readcount, to->number);
	}
	else {
		print = 0;
	}

	to->number = number;

#ifdef _DONETPROFILE_
	int startBytes, endBytes;
#endif

	field = entityStateFields;

	for (i = 0; i < lc; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);

#ifdef _DONETPROFILE_
		startBytes = msg->readcount;
#endif
		if (!MSG_ReadBits(msg, 1)) {
			// no change
			*toF = *fromF;
		}
		else {
			if (field->bits == 0) {
				// float
				if (MSG_ReadBits(msg, 1) == 0) {
					*(float*)toF = 0.0f;
				}
				else {
					if (MSG_ReadBits(msg, 1) == 0) {
						// integral float
						trunc = MSG_ReadBits(msg, FLOAT_INT_BITS);
						// bias to allow equal parts positive and negative
						trunc -= FLOAT_INT_BIAS;
						*(float*)toF = trunc;
						if (print) {
							Com_Printf("%s:%i ", field->name, trunc);
						}
					}
					else {
						// full floating point value
						*toF = MSG_ReadBits(msg, 32);
						if (print) {
							Com_Printf("%s:%f ", field->name, *(float*)toF);
						}
					}
				}
			}
			else {
				if (MSG_ReadBits(msg, 1) == 0) {
					*toF = 0;
				}
				else {
					// integer
					*toF = MSG_ReadBits(msg, field->bits);
					if (print) {
						Com_Printf("%s:%i ", field->name, *toF);
					}
				}
			}
			//			pcount[i]++;
		}
#ifdef _DONETPROFILE_
		endBytes = msg->readcount;
		ClReadProf().AddField(field->name, endBytes - startBytes);
#endif
	}

	field = &entityStateFields[lc];

	for (i = lc; i < numFields; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);
		// no change
		*toF = *fromF;
	}

	if (print) {
		if (msg->bit == 0) {
			endBit = msg->readcount * 8 - GENTITYNUM_BITS;
		}
		else {
			endBit = (msg->readcount - 1) * 8 + msg->bit - GENTITYNUM_BITS;
		}
		Com_Printf(" (%i bits)\n", endBit - startBit);
	}
}


/*
Ghoul2 Insert End
*/

/*
============================================================================

plyer_state_t communication

============================================================================
*/

// using the stringizing operator to save typing...
#define	PSF(x) #x,(int)&((playerState_t*)0)->x

static const netField_t	playerStateFields[] = 
{
{ PSF(commandTime), 32 },
{ PSF(pm_type), 8 },
{ PSF(bobCycle), 8 },
{ PSF(pm_flags), 17 },
{ PSF(pm_time), -16 },
{ PSF(origin[0]), 0 },
{ PSF(origin[1]), 0 },
{ PSF(origin[2]), 0 },
{ PSF(velocity[0]), 0 },
{ PSF(velocity[1]), 0 },
{ PSF(velocity[2]), 0 },
{ PSF(weaponTime), -16 },
{ PSF(weaponChargeTime), 32 }, //? really need 32 bits??
{ PSF(gravity), 16 },
{ PSF(leanofs), -8 },
{ PSF(friction), 16 },
{ PSF(speed), 16 },
{ PSF(delta_angles[0]), 16 },
{ PSF(delta_angles[1]), 16 },
{ PSF(delta_angles[2]), 16 },
{ PSF(groundEntityNum), GENTITYNUM_BITS },
//{ PSF(animationTimer), 16 },
{ PSF(legsAnim), 16 },
{ PSF(torsoAnim), 16 },
{ PSF(movementDir), 4 },
{ PSF(eFlags), 32 },
{ PSF(eventSequence), 16 },
{ PSF(events[0]), 8 },
{ PSF(events[1]), 8 },
{ PSF(eventParms[0]), -9 },
{ PSF(eventParms[1]), -9 },
{ PSF(externalEvent), 8 },
{ PSF(externalEventParm), 8 },
{ PSF(clientNum), 32 },
{ PSF(weapon), 5 },
{ PSF(weaponstate),	  4 },
{ PSF(batteryCharge),	16 },
{ PSF(viewangles[0]), 0 },
{ PSF(viewangles[1]), 0 },
{ PSF(viewangles[2]), 0 },
{ PSF(viewheight), -8 },
{ PSF(damageEvent), 8 },
{ PSF(damageYaw), 8 },
{ PSF(damagePitch), -8 },
{ PSF(damageCount), 8 },
{ PSF(saberColor), 8 },
{ PSF(saberActive), 8 },
{ PSF(saberLength), 32 },
{ PSF(saberLengthMax), 32 },
{ PSF(forcePowersActive), 32},
{ PSF(saberInFlight), 8 },
{ PSF(vehicleModel), 32 },
{ PSF(viewEntity), 32 },
{ PSF(serverViewOrg[0]), 0 },
{ PSF(serverViewOrg[1]), 0 },
{ PSF(serverViewOrg[2]), 0 },
};

/*
=============
MSG_WriteDeltaPlayerstate

=============
*/
void MSG_WriteDeltaPlayerstate(msg_t* msg, struct playerState_s* from, struct playerState_s* to) {
	int				i;
	playerState_t	dummy;
	int				statsbits;
	int				persistantbits;
	int				ammobits;
	int				powerupbits;
	int				inventorybits;
	int				numFields;
	int				c;
	const netField_t* field;
	int* fromF, * toF;
	float			fullFloat;
	int				trunc, lc;
	int				fieldIndex;

	if (!from) {
		from = &dummy;
		memset(&dummy, 0, sizeof(dummy));
	}

	c = msg->cursize;

	numFields = sizeof(playerStateFields) / sizeof(playerStateFields[0]);


	lc = 0;
	field = playerStateFields;

	for (i = 0; i < numFields; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);
		if (*fromF != *toF) {
			lc = i + 1;
		}
	}

	MSG_WriteByte(msg, lc);	// # of changes


	field = playerStateFields;

	for (i = 0; i < lc; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);

		if (*fromF == *toF) {
			MSG_WriteBits(msg, 0, 1);	// no change
			continue;
		}

		MSG_WriteBits(msg, 1, 1);	// changed
		//		pcount[i]++;

		if (field->bits == 0) {
			// float
			fullFloat = *(float*)toF;
			trunc = (int)fullFloat;

			if (trunc == fullFloat && trunc + FLOAT_INT_BIAS >= 0 &&
				trunc + FLOAT_INT_BIAS < (1 << FLOAT_INT_BITS)) {
				// send as small integer
				MSG_WriteBits(msg, 0, 1);
				MSG_WriteBits(msg, trunc + FLOAT_INT_BIAS, FLOAT_INT_BITS);
			}
			else {
				// send as full floating point value
				MSG_WriteBits(msg, 1, 1);
				MSG_WriteBits(msg, *toF, 32);
			}
		}
		else {
			// integer
			MSG_WriteBits(msg, *toF, field->bits);
		}
	}
	c = msg->cursize - c;

	//
	// send the arrays
	//
	statsbits = 0;
	for (i = 0; i < 16; i++) {
		if (to->stats[i] != from->stats[i]) {
			statsbits |= 1 << i;
		}
	}
	persistantbits = 0;
	for (i = 0; i < 16; i++) {
		if (to->persistant[i] != from->persistant[i]) {
			persistantbits |= 1 << i;
		}
	}
	ammobits = 0;
	for (i = 0; i < 10; i++) {
		if (to->ammo[i] != from->ammo[i]) {
			ammobits |= 1 << i;
		}
	}
	powerupbits = 0;
	for (i = 0; i < 16; i++) {
		if (to->powerups[i] != from->powerups[i]) {
			powerupbits |= 1 << i;
		}
	}
	inventorybits = 0;
	for (i = 0; i < 15; i++) {
		if (to->inventory[i] != from->inventory[i]) {
			inventorybits |= 1 << i;
		}
	}

	if (!statsbits && !persistantbits && !ammobits && !powerupbits) {
		MSG_WriteBits(msg, 0, 1);	// no change
		return;
	}
	MSG_WriteBits(msg, 1, 1);	// changed

	if (statsbits) {
		MSG_WriteBits(msg, 1, 1);	// changed
		MSG_WriteShort(msg, statsbits);
		for (fieldIndex = 0; fieldIndex < 16; fieldIndex++)
			if (statsbits & (1 << fieldIndex))
				MSG_WriteSShort(msg, to->stats[fieldIndex]);
		fieldIndex = 0;
	}
	else {
		MSG_WriteBits(msg, 0, 1);	// no change
	}


	if (persistantbits) {
		MSG_WriteBits(msg, 1, 1);	// changed
		MSG_WriteShort(msg, persistantbits);
		for (fieldIndex = 0; fieldIndex < 16; fieldIndex++)
			if (persistantbits & (1 << fieldIndex))
				MSG_WriteSShort(msg, to->persistant[fieldIndex]);
		fieldIndex = 0;
	}
	else {
		MSG_WriteBits(msg, 0, 1);	// no change
	}


	if (ammobits) {
		MSG_WriteBits(msg, 1, 1);	// changed
		MSG_WriteShort(msg, ammobits);
		for (fieldIndex = 0; fieldIndex < 16; fieldIndex++)
			if (ammobits & (1 << fieldIndex))
				MSG_WriteSShort(msg, to->ammo[fieldIndex]);
		fieldIndex = 0;
	}
	else {
		MSG_WriteBits(msg, 0, 1);	// no change
	}


	if (powerupbits) {
		MSG_WriteBits(msg, 1, 1);	// changed
		MSG_WriteShort(msg, powerupbits);
		for (fieldIndex = 0; fieldIndex < 16; fieldIndex++)
			if (powerupbits & (1 << fieldIndex))
				MSG_WriteLong(msg, to->powerups[fieldIndex]);
		fieldIndex = 0;
	}
	else {
		MSG_WriteBits(msg, 0, 1);	// no change
	}

	if (inventorybits) {
		MSG_WriteBits(msg, 1, 1);	// changed
		MSG_WriteShort(msg, inventorybits);
		for (fieldIndex = 0; fieldIndex < 16; fieldIndex++)
			if (inventorybits & (1 << fieldIndex))
				MSG_WriteShort(msg, to->inventory[fieldIndex]);
		fieldIndex = 0;
	}
	else {
		MSG_WriteBits(msg, 0, 1);	// no change
	}
}


/*
===================
MSG_ReadDeltaPlayerstate
===================
*/
void MSG_ReadDeltaPlayerstate(msg_t* msg, playerState_t* from, playerState_t* to) {
	int			i, lc;
	int			bits;
	const netField_t* field;
	int			numFields;
	int			startBit, endBit;
	int			print;
	int* fromF, * toF;
	int			trunc;
	playerState_t	dummy;

	if (!from) {
		from = &dummy;
		memset(&dummy, 0, sizeof(dummy));
	}
	*to = *from;

	if (msg->bit == 0) {
		startBit = msg->readcount * 8 - GENTITYNUM_BITS;
	}
	else {
		startBit = (msg->readcount - 1) * 8 + msg->bit - GENTITYNUM_BITS;
	}

	// shownet 2/3 will interleave with other printed info, -2 will
	// just print the delta records
	if (cl_shownet->integer >= 2 || cl_shownet->integer == -2) {
		print = 1;
		Com_Printf("%3i: playerstate ", msg->readcount);
	}
	else {
		print = 0;
	}

	numFields = sizeof(playerStateFields) / sizeof(playerStateFields[0]);
	lc = MSG_ReadByte(msg);


	field = playerStateFields;

	for (i = 0; i < lc; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);

		if (!MSG_ReadBits(msg, 1)) {
			// no change
			*toF = *fromF;
		}
		else {
			if (field->bits == 0) {
				// float
				if (MSG_ReadBits(msg, 1) == 0) {
					// integral float
					trunc = MSG_ReadBits(msg, FLOAT_INT_BITS);
					// bias to allow equal parts positive and negative
					trunc -= FLOAT_INT_BIAS;
					*(float*)toF = trunc;
					if (print) {
						Com_Printf("%s:%i ", field->name, trunc);
					}
				}
				else {
					// full floating point value
					*toF = MSG_ReadBits(msg, 32);
					if (print) {
						Com_Printf("%s:%f ", field->name, *(float*)toF);
					}
				}
			}
			else {
				// integer
				*toF = MSG_ReadBits(msg, field->bits);
				if (print) {
					Com_Printf("%s:%i ", field->name, *toF);
				}
			}
		}
	}

	field = &playerStateFields[lc];

	for (i = lc; i < numFields; i++, field++) {
		fromF = (int*)((byte*)from + field->offset);
		toF = (int*)((byte*)to + field->offset);
		// no change
		*toF = *fromF;
	}

	// read the arrays
	if (MSG_ReadBits(msg, 1)) {
		// parse stats
		if (MSG_ReadBits(msg, 1)) {
			LOG("PS_STATS");
			bits = MSG_ReadShort(msg);
			for (i = 0; i < 16; i++) {
				if (bits & (1 << i)) {
					to->stats[i] = MSG_ReadSShort(msg);
				}
			}
		}

		// parse persistant stats
		if (MSG_ReadBits(msg, 1)) {
			LOG("PS_PERSISTANT");
			bits = MSG_ReadShort(msg);
			for (i = 0; i < 16; i++) {
				if (bits & (1 << i)) {
					to->persistant[i] = MSG_ReadSShort(msg);
				}
			}
		}

		// parse ammo
		if (MSG_ReadBits(msg, 1)) {
			LOG("PS_AMMO");
			bits = MSG_ReadShort(msg);
			for (i = 0; i < 16; i++) {
				if (bits & (1 << i)) {
					to->ammo[i] = MSG_ReadSShort(msg);
				}
			}
		}

		// parse powerups
		if (MSG_ReadBits(msg, 1)) {
			LOG("PS_POWERUPS");
			bits = MSG_ReadShort(msg);
			for (i = 0; i < 16; i++) {
				if (bits & (1 << i)) {
					to->powerups[i] = MSG_ReadLong(msg);
				}
			}
		}

		// parse inventory
		if (MSG_ReadBits(msg, 1)) {
			LOG("PS_INVENTORY");
			bits = MSG_ReadShort(msg);
			for (i = 0; i < 16; i++) {
				if (bits & (1 << i)) {
					to->inventory[i] = MSG_ReadShort(msg);
				}
			}
		}
	}

	if (print) {
		if (msg->bit == 0) {
			endBit = msg->readcount * 8 - GENTITYNUM_BITS;
		}
		else {
			endBit = (msg->readcount - 1) * 8 + msg->bit - GENTITYNUM_BITS;
		}
		Com_Printf(" (%i bits)\n", endBit - startBit);
	}
}


//===========================================================================
