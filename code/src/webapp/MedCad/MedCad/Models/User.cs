using Newtonsoft.Json;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MedCad.Models
{
    public class User
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [JsonIgnore]
        public int UserId { get; set; }

        public string Email { get; set; }

        public string RegisteredAt { get; set; }
        
        [JsonIgnore]
        public virtual Model Model { get; set; }

        [JsonIgnore]
        //[ForeignKey("Model")]
        public int ModelId { get; set; }
    }
}
