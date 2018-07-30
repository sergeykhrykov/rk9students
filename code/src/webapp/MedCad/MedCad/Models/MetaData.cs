using Newtonsoft.Json;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MedCad.Models
{
    public class MetaData
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [JsonIgnore]
        public int MetaDataId { get; set; }

        public string CreatedAt { get; set; }

        public string Name { get; set; }

        public int TriangleCount { get; set; }

        public string ModifiedAt { get; set; }

        public int LastVersion { get; set; }
        
        [JsonIgnore]
        public virtual Model Model { get; set; }

        //[ForeignKey("Model")]
        [JsonIgnore]
        public int ModelId { get; set; }
    }
}
