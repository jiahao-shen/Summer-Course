package com.sam;

import clojure.lang.PersistentArrayMap;
import org.apache.storm.scheduler.*;

import java.util.*;

/**
 * @author 沈嘉浩、赵佳豪
 */
public class MyScheduler implements IScheduler {

    public void prepare(Map conf) {
    }

    public void schedule(Topologies topologies, Cluster cluster) {
        System.out.println("MyScheduler: Begin scheduling");
        //获取我们想要调度的拓扑
        Collection<TopologyDetails> topologyDetails = topologies.getTopologies();
        //作业是否要指定分配的标识
        String assignedFlag;
        Map map;
        for (TopologyDetails td : topologyDetails) {   //遍历所有的拓扑
            map = td.getConf();     //获取拓扑Conf
            assignedFlag = (String) map.get("assigned_flag");    //根据Conf的键assigned_flag获取值

            //如何找到的拓扑的分配标为1则代表是要分配的,否则采用系统的调度
            if (assignedFlag != null && assignedFlag.equals("1")) {
                System.out.println("Finding topology named " + td.getName());
                //采用调度策略
                topologyAssign(cluster, td, map);
            } else {
                System.out.println("Topology assigned is null");
            }
        }

        //其余的任务由系统自带的调度器执行
        new EvenScheduler().schedule(topologies, cluster);
    }

    /**
     * 拓扑逻辑的调度
     *
     * @param cluster  集群
     * @param topology 具体要调度的拓扑逻辑
     * @param map      map配置项
     */
    private void topologyAssign(Cluster cluster, TopologyDetails topology, Map map) {
        Set keys;
        PersistentArrayMap designMap;
        Iterator iterator = null;

        if (topology != null) {
            designMap = (PersistentArrayMap) map.get("designed_map");
            if (designMap != null) {
                System.out.println("Design map size is " + designMap.size());
                keys = designMap.keySet();
                iterator = keys.iterator();
            }

            if (designMap == null || designMap.size() == 0) {
                System.out.println("Design map is null");
            }

            boolean needsScheduling = cluster.needsScheduling(topology);

            //如果不需要调度
            if (!needsScheduling) {
                System.out.println("Our special topology does not need scheduling");
            } else {
                System.out.println("Our special topology needs scheduling");
                //找到所有需要调度的拓扑的组件
                Map<String, List<ExecutorDetails>> componentToExecutors = cluster.getNeedsSchedulingComponentToExecutors(topology);

                System.out.println("Needs scheduling(component->executor): " + componentToExecutors);
                System.out.println("Needs scheduling(executor->components): " + cluster.getNeedsSchedulingExecutorToComponents(topology));
                SchedulerAssignment currentAssignment = cluster.getAssignmentById(topology.getId());
                if (currentAssignment != null) {
                    System.out.println("Current assignments: " + currentAssignment.getExecutorToSlot());
                } else {
                    System.out.println("Current assignments: {}");
                }

                Object componentName;
                String nodeName;
                if (designMap != null) {
                    while (iterator.hasNext()) {
                        componentName = iterator.next();
                        nodeName = (String) designMap.get(componentName);

                        System.out.println("Scheduling componentName->nodeName:" + componentName + "->" + nodeName);
                        componentAssign(cluster, topology, componentToExecutors, componentName, nodeName);
                    }
                }
            }
        }
    }

    /**
     * 组件调度
     *
     * @param cluster        集群的信息
     * @param topology       待调度的拓扑细节信息
     * @param totalExecutors 组件的执行器
     * @param componentName  组件的名称
     * @param supervisorName 节点的名称
     */
    private void componentAssign(Cluster cluster, TopologyDetails topology, Map<String, List<ExecutorDetails>> totalExecutors, Object componentName, String supervisorName) {
        if (!totalExecutors.containsKey(componentName)) {
            System.out.println("Our special-spout does not need scheduling");
        } else {
            System.out.println("Our special-spout needs scheduling");
            List<ExecutorDetails> executors = totalExecutors.get(componentName);

            Collection<SupervisorDetails> supervisors = cluster.getSupervisors().values();
            SupervisorDetails specialSupervisor = null;
            for (SupervisorDetails supervisor : supervisors) {
                Map meta = (Map) supervisor.getSchedulerMeta();

                if (meta != null && meta.get("name") != null) {
                    System.out.println("Supervisor name:" + meta.get("name"));

                    if (meta.get("name").equals(supervisorName)) {
                        System.out.println("Supervisor finding");
                        specialSupervisor = supervisor;
                        break;
                    }
                } else {
                    System.out.println("Supervisor meta null");
                }

            }

            //找到特殊的supervisor
            if (specialSupervisor != null) {
                System.out.println("Found the special-supervisor");
                List<WorkerSlot> availableSlots = cluster.getAvailableSlots(specialSupervisor);

                //如果目标节点上已经没有空闲的slot,则进行强制释放
                if (availableSlots.isEmpty() && !executors.isEmpty()) {
                    for (Integer port : cluster.getUsedPorts(specialSupervisor)) {
                        cluster.freeSlot(new WorkerSlot(specialSupervisor.getId(), port));
                    }
                }

                //重新获取可用的slot
                availableSlots = cluster.getAvailableSlots(specialSupervisor);

                //选取节点上第一个slot,进行分配
                cluster.assign(availableSlots.get(0), topology.getId(), executors);
                System.out.println("We assigned executors:" + executors + " to slot: [" + availableSlots.get(0).getNodeId() + ", " + availableSlots.get(0).getPort() + "]");
            } else {
                System.out.println("There is no supervisor find!!!");
            }
        }
    }
}