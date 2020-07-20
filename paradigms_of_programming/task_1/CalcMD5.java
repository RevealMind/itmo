import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.util.List;


public class CalcMD5 {
    public static void main(String[] args) throws Exception{
        List<String> FileList = Files.readAllLines(Paths.get(args[0]));
        for (String testFile : FileList) {
            byte byteData[] = Files.readAllBytes(Paths.get(testFile));
            MessageDigest md5 = MessageDigest.getInstance("MD5");
            byte out[] = md5.digest(byteData);
            for (byte md5out : out) {
                System.out.printf("%02X", md5out);
            }
            System.out.println();
        }
    }
}