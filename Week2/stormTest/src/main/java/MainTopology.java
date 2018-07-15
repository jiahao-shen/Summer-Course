import org.apache.storm.Config;
import org.apache.storm.LocalCluster;
import org.apache.storm.StormSubmitter;
import org.apache.storm.generated.AlreadyAliveException;
import org.apache.storm.generated.AuthorizationException;
import org.apache.storm.generated.InvalidTopologyException;
import org.apache.storm.topology.TopologyBuilder;

public class MainTopology {

    public void runLocal(int waitSeconds) {
        TopologyBuilder builder = new TopologyBuilder();
        builder.setSpout("wordSpout", new WordSpout(), 5);
        builder.setBolt("countBolt", new CountBolt(), 12).shuffleGrouping("wordSpout");

        Config config = new Config();
        config.setDebug(true);
        config.setNumWorkers(3);
        config.setMaxTaskParallelism(3);

        LocalCluster cluster = new LocalCluster();
        try {
            StormSubmitter.submitTopologyWithProgressBar("word_count", config, builder.createTopology());
        } catch (AlreadyAliveException e) {
            e.printStackTrace();
        } catch (InvalidTopologyException e) {
            e.printStackTrace();
        } catch (AuthorizationException e) {
            e.printStackTrace();
        }

        try {
            Thread.sleep(waitSeconds * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        cluster.killTopology("word_count");
        cluster.shutdown();
    }

    public static void main(String[] args) {
        MainTopology topology = new MainTopology();
        topology.runLocal(60);
    }
}
