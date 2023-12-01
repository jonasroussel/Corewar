.name       "test"
.comment    "Un premier champion vraiment nul"

label_test: live    %1
            ld %0, r2
stock_num:  st  r1, -11
    zjmp    %:label_test
