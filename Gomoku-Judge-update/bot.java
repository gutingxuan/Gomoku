import java.util.*;
import org.json.simple.JSONValue;

class Main {
	static class Grid {
		public static final int SIZE = 15;
		private int[][] grid = new int[SIZE][SIZE];
		public void placeAt(int x, int y) {
			if (x >= 0 && y >= 0) {
				grid[x][y] = 1;
			}
		}
		public Map randomAvailablePosition() {
			List xList = new LinkedList();
			List yList = new LinkedList();
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (grid[i][j] == 0) {
						xList.add(i);
						yList.add(j);
					}
				}
			}
			int rand = (int) (Math.random()*xList.size());
			Map map = new HashMap();
			map.put("x", xList.get(rand));
			map.put("y", yList.get(rand));
			return map;
		}
	}
	public static void main(String[] args) {
		String input = new Scanner(System.in).nextLine();
		Map<String, List> obj = (Map) JSONValue.parse(input);
		Grid grid = new Grid();
		List<Map> requests = obj.get("requests");
		List<Map> responses = obj.get("responses");
		for (Map<String, Long> rec : requests) {
			grid.placeAt(rec.get("x").intValue(), rec.get("y").intValue());
		}
		for (Map<String, Long> rec : responses) {
			grid.placeAt(rec.get("x").intValue(), rec.get("y").intValue());
		}
		Map output = new HashMap();
		output.put("response", grid.randomAvailablePosition());
		System.out.print(JSONValue.toJSONString(output));
	}
}