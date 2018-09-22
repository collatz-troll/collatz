#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <vector>

class ax_plus_b {
public:
  int64_t a;
  int64_t b;

  ax_plus_b(int64_t aa = 0ll, int64_t bb = 0ll) : a(aa), b(bb) { }

  inline void substitute_for_x(const ax_plus_b& x_expr, ax_plus_b& res) const;
  inline bool even_odd_split(ax_plus_b& x_for_even, ax_plus_b& x_for_odd, ax_plus_b& even_case, ax_plus_b& odd_case) const;
};

inline void ax_plus_b::substitute_for_x(const ax_plus_b& x_expr, ax_plus_b& res) const {
  res.a = a * x_expr.a;
  res.b = a * x_expr.b + b;
}

inline bool ax_plus_b::even_odd_split(ax_plus_b& x_for_even, ax_plus_b& x_for_odd, ax_plus_b& even_case, ax_plus_b& odd_case) const {
  if ((a & 1ll) == 0ll) return false;
  if ((b & 1ll) == 0ll) {
    x_for_even.a = 2ll;
    x_for_even.b = 0ll;
    substitute_for_x(x_for_even, even_case);
    x_for_odd.a = 2ll;
    x_for_odd.b = -1ll;
    substitute_for_x(x_for_odd, odd_case);
  }
  else {
    x_for_even.a = 2ll;
    x_for_even.b = -1ll;
    substitute_for_x(x_for_even, even_case);
    x_for_odd.a = 2ll;
    x_for_odd.b = 0ll;
    substitute_for_x(x_for_odd, odd_case);
  }
  return true;
}

inline bool apply_collatz_iteration(const ax_plus_b& k, const ax_plus_b& t, ax_plus_b& k_for_down, ax_plus_b& t_for_down, ax_plus_b& k_for_up, ax_plus_b& t_for_up) {
  ax_plus_b r_for_down, r_for_up;
  if (t.even_odd_split(r_for_down, r_for_up, t_for_down, t_for_up)) {
    k.substitute_for_x(r_for_down, k_for_down);
    k.substitute_for_x(r_for_up, k_for_up);
    t_for_down.a /= 2ll;
    t_for_down.b /= 2ll;
    t_for_up.a /= 2ll;
    t_for_up.a *= 3ll;
    t_for_up.b *= 3ll;
    ++(t_for_up.b);
    t_for_up.b /= 2ll;
    return true;
  }
  else return false;
}

void print_trajectory(size_t bits, size_t msb) {
  size_t mask = 1ull << msb;
  while (mask) {
    fputc((bits&mask) ? '1' : '0', stdout);
    mask >>= 1;
  }
}

int main(int argc, char** argv) {
  if (argc==2) {
    size_t h = atoi(argv[1]);

    std::vector< std::vector<ax_plus_b> > ks(h), ts(h);
    ks[0].resize(2);
    ks[0][0].a=2; ks[0][0].b=0; ks[0][1].a=2; ks[0][1].b=-1;
    ts[0].resize(2);
    ts[0][0].a=1; ts[0][0].b=0; ts[0][1].a=3; ts[0][1].b=-1;

    print_trajectory(0,0);
    printf(" %lld*r%+lld to %lld*r%+lld\n", ks[0][0].a, ks[0][0].b, ts[0][0].a, ts[0][0].b);
    print_trajectory(1,0);
    printf(" %lld*r%+lld to %lld*r%+lld\n", ks[0][1].a, ks[0][1].b, ts[0][1].a, ts[0][1].b);

    size_t prev_size = 2;

    for(size_t i=1; i<h; ++i) {
      size_t cur_size = prev_size << 1;
      ks[i].resize(cur_size);
      ts[i].resize(cur_size);

      size_t j2=0;
      for(size_t j=0; j<prev_size; ++j, j2+=2) {
        apply_collatz_iteration(ks[i-1][j], ts[i-1][j], ks[i][j2], ts[i][j2], ks[i][j2+1], ts[i][j2+1]);
        print_trajectory(j2, i);
        printf(" %lld*r%+lld to %lld*r%+lld\n", ks[i][j2].a, ks[i][j2].b, ts[i][j2].a, ts[i][j2].b);
        print_trajectory(j2+1, i);
        printf(" %lld*r%+lld to %lld*r%+lld\n", ks[i][j2+1].a, ks[i][j2+1].b, ts[i][j2+1].a, ts[i][j2+1].b);
      }

      prev_size = cur_size;
    }
  } else printf("Syntax: %s <max_trajectory_length>\n", argv[0]);

  return 0;
}
