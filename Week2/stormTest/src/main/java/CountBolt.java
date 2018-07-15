import org.apache.storm.task.OutputCollector;
import org.apache.storm.task.TopologyContext;
import org.apache.storm.topology.OutputFieldsDeclarer;
import org.apache.storm.topology.base.BaseRichBolt;
import org.apache.storm.tuple.Fields;
import org.apache.storm.tuple.Tuple;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class CountBolt extends BaseRichBolt {
    private HashMap<String, Integer> wordMap = new HashMap<String, Integer>();

    public void prepare(Map map, TopologyContext topologyContext, OutputCollector outputCollector) {

    }

    public void execute(Tuple tuple) {
        String word = tuple.getStringByField("word");

        int num = wordMap.containsKey(word) ? wordMap.get(word) : 0;
        wordMap.put(word, num + 1);

//        Set<String> keys = wordMap.keySet();
//        for (String key: keys) {
//            System.out.print(key + ":" + wordMap.get(key) + ",");
//        }
//        System.out.println();
    }

    public void declareOutputFields(OutputFieldsDeclarer outputFieldsDeclarer) {
        outputFieldsDeclarer.declare(new Fields("word", "count"));
    }
}
