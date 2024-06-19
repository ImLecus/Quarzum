#pragma once
/**
 * TokenType values:
 * 0x00 - 0x2F : keywords
 * 0x30 - 0x5F: operators
 * 0x60 - 0x7F : symbols
 * 0x80 - 0x9F : literals
 * 0xF0 - 0xFF : other
*/
enum TokenType : unsigned char {
    // type keywords
    b_keyword = 0x00,
    i8_keyword = 0x01,
    i16_keyword = 0x02,
    i32_keyword = 0x03,
    i64_keyword = 0x04,
    u8_keyword = 0x05,
    u16_keyword = 0x06,
    u32_keyword = 0x07,
    u64_keyword = 0x08,
    num_keyword = 0x09,
    num64_keyword = 0x0A,
    decimal_keyword = 0x0B,
    char_keyword = 0x0C,
    string_keyword = 0x0D,
    var_keyword = 0x0E,
    function_keyword = 0x0F,
    // keywords
    const_keyword = 0x10,
    return_keyword = 0x11,
    module_keyword = 0x12,
    class_keyword = 0x13,
    if_keyword = 0x14,
    while_keyword = 0x15,
    exit_keyword = 0x16,
    import_keyword = 0x17,
    from_keyword = 0x18,
    continue_keyword = 0x19,
    break_keyword = 0x1A,
    enum_keyword = 0x1B,
    foreach_keyword = 0x1C,
    in_keyword = 0x1D,
    public_keyword = 0x1E,
    private_keyword = 0x1F,
    protected_keyword = 0x20,
    do_keyword = 0x21,
    for_keyword = 0x22,
    // operators
    plus = 0x30,
    converge_sum = 0x31,
    minus = 0x32,
    prod = 0x33,
    division = 0x34,
    mod = 0x35,
    or_op = 0x36,
    not_op = 0x37,
    and_op = 0x38,
    xor_op = 0x39,
    is_equal = 0x3A,
    not_equal = 0x3B,
    greater = 0x3C,
    lower = 0x3D,
    greater_eq = 0x3E,
    lower_eq = 0x3F,
    plus_unary = 0x40,
    minus_unary = 0x41,
    bit_or = 0x42,
    bit_and = 0x43,
    bit_xor = 0x44,
    bit_not = 0x45,

    plus_eq = 0x46,
    minus_eq = 047,
    prod_eq = 0x48,
    div_eq = 0x49,
    mod_eq = 0x4A,
    pow_eq = 0x4B,
    converge_eq = 0x4C,

    // symbols
    equal = 0x60,
    semicolon = 0x61,
    left_par = 0x62,
    right_par = 0x63,
    left_curly = 0x64,
    right_curly = 0x65,
    left_square = 0x66,
    right_square = 0x67,
    comma = 0x68,
    arrow = 0x69,
    // literals
    int_literal = 0x80,
    num_literal = 0x81,
    char_literal = 0x82,
    string_literal = 0x83,
    true_literal = 0x84,
    false_literal = 0x85,
    null_literal = 0x86,
    // other
    identifier = 0xF0,
    comment = 0xF1,
    p_optional = 0xF2,
    p_type = 0xF3,
    token_error = 0xFF
};
