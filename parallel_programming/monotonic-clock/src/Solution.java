import org.jetbrains.annotations.NotNull;

/**
 * В теле класса решения разрешено использовать только финальные переменные типа RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 */
public class Solution implements MonotonicClock {
    private final RegularInt c1 = new RegularInt(0);
    private final RegularInt c2 = new RegularInt(0);
    private final RegularInt c3 = new RegularInt(0);

    private final RegularInt b1 = new RegularInt(0);
    private final RegularInt b2 = new RegularInt(0);
    private final RegularInt b3 = new RegularInt(0);

    @Override
    public void write(@NotNull Time time) {
        b1.setValue(time.getD1());
        b2.setValue(time.getD2());
        b3.setValue(time.getD3());
        // write right-to-left
        c3.setValue(time.getD3());
        c2.setValue(time.getD2());
        c1.setValue(time.getD1());
    }

    @NotNull
    @Override
    public Time read() {
        int rc1 = c1.getValue();
        int rc2 = c2.getValue();
        int rc3 = c3.getValue();

        int rb3 = b3.getValue();
        int rb2 = b2.getValue();
        int rb1 = b1.getValue();

        if (rc1 == rb1) {
            if (rc2 == rb2) {
                if (rc3 == rb3) {
                    return new Time(rc1, rc2, rc3);
                } else {
                    return new Time(rc1, rc2, rb3);
                }
            } else {
                return new Time(rc1, rb2, 0);
            }
        } else {
            return new Time(rb1, 0, 0);
        }
    }
}
