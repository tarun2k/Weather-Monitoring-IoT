function doGet(e) { 
  Logger.log( JSON.stringify(e) );
  var result = 'Ok';
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '1GACfW8z2LpSHv83C4Ro3y5KP8eHbZW4MHJLGQGl2Tb4'; 	// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    rowData[0] = new Date(); 	
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'temperature':
          rowData[1] = value; 
          result = 'Written on column B';
          break;
        case 'humidity':
          rowData[2] = value;
          result += ' ,Written on column C';
          break;  
        case 'gas':
          rowData[3] = value;
          result += ' ,Written on column D';
          break; 
        case 'volt':
          rowData[4] = value;
          result += ' ,Written on column E';
          break;  
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  return ContentService.createTextOutput(result);
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
