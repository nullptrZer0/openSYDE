# This file lists all libtommath files and include paths in qmake syntax.
# It can be included from a qmake .pro file

#shout out aloud so we have a clearly distinguishable headline in the log:
message("libtommath.pri: --------------------- ADDING PACKAGES ---------------------")

# basics:
INCLUDEPATH += $${PWD}

SOURCES += \
    $${PWD}/bn_cutoffs.c \
    $${PWD}/bn_deprecated.c \
    $${PWD}/bn_mp_2expt.c \
    $${PWD}/bn_mp_abs.c \
    $${PWD}/bn_mp_add.c \
    $${PWD}/bn_mp_addmod.c \
    $${PWD}/bn_mp_add_d.c \
    $${PWD}/bn_mp_and.c \
    $${PWD}/bn_mp_clamp.c \
    $${PWD}/bn_mp_clear.c \
    $${PWD}/bn_mp_clear_multi.c \
    $${PWD}/bn_mp_cmp.c \
    $${PWD}/bn_mp_cmp_d.c \
    $${PWD}/bn_mp_cmp_mag.c \
    $${PWD}/bn_mp_cnt_lsb.c \
    $${PWD}/bn_mp_complement.c \
    $${PWD}/bn_mp_copy.c \
    $${PWD}/bn_mp_count_bits.c \
    $${PWD}/bn_mp_decr.c \
    $${PWD}/bn_mp_div.c \
    $${PWD}/bn_mp_div_2.c \
    $${PWD}/bn_mp_div_2d.c \
    $${PWD}/bn_mp_div_3.c \
    $${PWD}/bn_mp_div_d.c \
    $${PWD}/bn_mp_dr_is_modulus.c \
    $${PWD}/bn_mp_dr_reduce.c \
    $${PWD}/bn_mp_dr_setup.c \
    $${PWD}/bn_mp_error_to_string.c \
    $${PWD}/bn_mp_exch.c \
    $${PWD}/bn_mp_exptmod.c \
    $${PWD}/bn_mp_expt_u32.c \
    $${PWD}/bn_mp_exteuclid.c \
    $${PWD}/bn_mp_fread.c \
    $${PWD}/bn_mp_from_sbin.c \
    $${PWD}/bn_mp_from_ubin.c \
    $${PWD}/bn_mp_fwrite.c \
    $${PWD}/bn_mp_gcd.c \
    $${PWD}/bn_mp_get_double.c \
    $${PWD}/bn_mp_get_i32.c \
    $${PWD}/bn_mp_get_i64.c \
    $${PWD}/bn_mp_get_l.c \
    $${PWD}/bn_mp_get_ll.c \
    $${PWD}/bn_mp_get_mag_u32.c \
    $${PWD}/bn_mp_get_mag_u64.c \
    $${PWD}/bn_mp_get_mag_ul.c \
    $${PWD}/bn_mp_get_mag_ull.c \
    $${PWD}/bn_mp_grow.c \
    $${PWD}/bn_mp_incr.c \
    $${PWD}/bn_mp_init.c \
    $${PWD}/bn_mp_init_copy.c \
    $${PWD}/bn_mp_init_i32.c \
    $${PWD}/bn_mp_init_i64.c \
    $${PWD}/bn_mp_init_l.c \
    $${PWD}/bn_mp_init_ll.c \
    $${PWD}/bn_mp_init_multi.c \
    $${PWD}/bn_mp_init_set.c \
    $${PWD}/bn_mp_init_size.c \
    $${PWD}/bn_mp_init_u32.c \
    $${PWD}/bn_mp_init_u64.c \
    $${PWD}/bn_mp_init_ul.c \
    $${PWD}/bn_mp_init_ull.c \
    $${PWD}/bn_mp_invmod.c \
    $${PWD}/bn_mp_iseven.c \
    $${PWD}/bn_mp_isodd.c \
    $${PWD}/bn_mp_is_square.c \
    $${PWD}/bn_mp_kronecker.c \
    $${PWD}/bn_mp_lcm.c \
    $${PWD}/bn_mp_log_u32.c \
    $${PWD}/bn_mp_lshd.c \
    $${PWD}/bn_mp_mod.c \
    $${PWD}/bn_mp_mod_2d.c \
    $${PWD}/bn_mp_mod_d.c \
    $${PWD}/bn_mp_montgomery_calc_normalization.c \
    $${PWD}/bn_mp_montgomery_reduce.c \
    $${PWD}/bn_mp_montgomery_setup.c \
    $${PWD}/bn_mp_mul.c \
    $${PWD}/bn_mp_mulmod.c \
    $${PWD}/bn_mp_mul_2.c \
    $${PWD}/bn_mp_mul_2d.c \
    $${PWD}/bn_mp_mul_d.c \
    $${PWD}/bn_mp_neg.c \
    $${PWD}/bn_mp_or.c \
    $${PWD}/bn_mp_pack.c \
    $${PWD}/bn_mp_pack_count.c \
    $${PWD}/bn_mp_prime_fermat.c \
    $${PWD}/bn_mp_prime_frobenius_underwood.c \
    $${PWD}/bn_mp_prime_is_prime.c \
    $${PWD}/bn_mp_prime_miller_rabin.c \
    $${PWD}/bn_mp_prime_next_prime.c \
    $${PWD}/bn_mp_prime_rabin_miller_trials.c \
    $${PWD}/bn_mp_prime_rand.c \
    $${PWD}/bn_mp_prime_strong_lucas_selfridge.c \
    $${PWD}/bn_mp_radix_size.c \
    $${PWD}/bn_mp_radix_smap.c \
    $${PWD}/bn_mp_rand.c \
    $${PWD}/bn_mp_read_radix.c \
    $${PWD}/bn_mp_reduce.c \
    $${PWD}/bn_mp_reduce_2k.c \
    $${PWD}/bn_mp_reduce_2k_l.c \
    $${PWD}/bn_mp_reduce_2k_setup.c \
    $${PWD}/bn_mp_reduce_2k_setup_l.c \
    $${PWD}/bn_mp_reduce_is_2k.c \
    $${PWD}/bn_mp_reduce_is_2k_l.c \
    $${PWD}/bn_mp_reduce_setup.c \
    $${PWD}/bn_mp_root_u32.c \
    $${PWD}/bn_mp_rshd.c \
    $${PWD}/bn_mp_sbin_size.c \
    $${PWD}/bn_mp_set.c \
    $${PWD}/bn_mp_set_double.c \
    $${PWD}/bn_mp_set_i32.c \
    $${PWD}/bn_mp_set_i64.c \
    $${PWD}/bn_mp_set_l.c \
    $${PWD}/bn_mp_set_ll.c \
    $${PWD}/bn_mp_set_u32.c \
    $${PWD}/bn_mp_set_u64.c \
    $${PWD}/bn_mp_set_ul.c \
    $${PWD}/bn_mp_set_ull.c \
    $${PWD}/bn_mp_shrink.c \
    $${PWD}/bn_mp_signed_rsh.c \
    $${PWD}/bn_mp_sqr.c \
    $${PWD}/bn_mp_sqrmod.c \
    $${PWD}/bn_mp_sqrt.c \
    $${PWD}/bn_mp_sqrtmod_prime.c \
    $${PWD}/bn_mp_sub.c \
    $${PWD}/bn_mp_submod.c \
    $${PWD}/bn_mp_sub_d.c \
    $${PWD}/bn_mp_to_radix.c \
    $${PWD}/bn_mp_to_sbin.c \
    $${PWD}/bn_mp_to_ubin.c \
    $${PWD}/bn_mp_ubin_size.c \
    $${PWD}/bn_mp_unpack.c \
    $${PWD}/bn_mp_xor.c \
    $${PWD}/bn_mp_zero.c \
    $${PWD}/bn_prime_tab.c \
    $${PWD}/bn_s_mp_add.c \
    $${PWD}/bn_s_mp_balance_mul.c \
    $${PWD}/bn_s_mp_exptmod.c \
    $${PWD}/bn_s_mp_exptmod_fast.c \
    $${PWD}/bn_s_mp_get_bit.c \
    $${PWD}/bn_s_mp_invmod_fast.c \
    $${PWD}/bn_s_mp_invmod_slow.c \
    $${PWD}/bn_s_mp_karatsuba_mul.c \
    $${PWD}/bn_s_mp_karatsuba_sqr.c \
    $${PWD}/bn_s_mp_montgomery_reduce_fast.c \
    $${PWD}/bn_s_mp_mul_digs.c \
    $${PWD}/bn_s_mp_mul_digs_fast.c \
    $${PWD}/bn_s_mp_mul_high_digs.c \
    $${PWD}/bn_s_mp_mul_high_digs_fast.c \
    $${PWD}/bn_s_mp_prime_is_divisible.c \
    $${PWD}/bn_s_mp_rand_jenkins.c \
    $${PWD}/bn_s_mp_rand_platform.c \
    $${PWD}/bn_s_mp_reverse.c \
    $${PWD}/bn_s_mp_sqr.c \
    $${PWD}/bn_s_mp_sqr_fast.c \
    $${PWD}/bn_s_mp_sub.c \
    $${PWD}/bn_s_mp_toom_mul.c \
    $${PWD}/bn_s_mp_toom_sqr.c 

HEADERS += \
    $${PWD}/tommath.h \
    $${PWD}/tommath_class.h \
    $${PWD}/tommath_cutoffs.h \
    $${PWD}/tommath_private.h \
    $${PWD}/tommath_superclass.h